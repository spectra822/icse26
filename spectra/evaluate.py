import pandas as pd
from pathlib import Path
from datetime import datetime
import argparse
import re
import numpy as np

from data_helpers import CodeNetVerifier
from utils import RichLog

if __name__ == "__main__":
    
    parser = argparse.ArgumentParser(description='Translation Evaluator')
    parser.add_argument('-dir', dest="dir", required=True, type=str, help="Directory containing the translated files")
    parser.add_argument('-results_file', dest="results_file", default='../results.csv', type=str, help="File to save the results")
    parser.add_argument('-pattern', dest="pattern", default=".*", type=str, help="Pattern to match the files")
    parser.add_argument('-oneshot', dest="oneshot", default=False, action='store_true', help="Use oneshot specs")
    parser.add_argument('-append', dest="append", default=False, action='store_true', help="Append to the existing results file")
    args = parser.parse_args()

    cnv             = CodeNetVerifier()
    prompts_dir     = Path(args.dir)

    assert prompts_dir.exists()

    results_file         = Path(args.results_file)

    if results_file.exists() and args.append:
        results = pd.read_csv(results_file, sep="\t")
        results = results.set_index(['problem_id', 'solution_id'])
    else:
        results = pd.DataFrame(columns=['problem_id', 'solution_id'])
        results = results.set_index(['problem_id', 'solution_id'])

    col_names = set()

    for problem_dir in prompts_dir.iterdir():

        if not problem_dir.is_dir():
            continue

        problem_id = problem_dir.name

        for solution_file in problem_dir.iterdir():

            if '_prompt' in solution_file.stem:
                continue
            
            if not re.match(args.pattern, solution_file.stem):
                continue

            sol_id          = solution_file.stem.split('_')[0]
            # technique       = solution_file.stem.split('_')[1]
            source_language = solution_file.stem.split('_')[2]
            target_language = solution_file.stem.split('_')[3]
            # assert target_language == "rust"
            model           = solution_file.stem.split('_')[4]
            translated      = solution_file.read_text()

            source_language, technique = source_language.split('-')
            if args.oneshot:
                technique_map = {'gen0': 'baseline',
                                'gen1': 'invariant-oneshot',
                                'gen2': 'test-oneshot',
                                'gen3': 'desc-oneshot'}
            else:
                technique_map = {'gen0': 'baseline',
                                'gen1': 'invariant',
                                'gen2': 'test',
                                'gen3': 'desc'}
                             
            technique = technique_map[technique]

            if len(model.split('-')) > 1:
                assert len(model.split('-')) == 2
                model, candidate_num = model.split('-')
            else:
                candidate_num = None

            if candidate_num is not None:
                col_name = f'{model} {source_language} to {target_language} {technique} {candidate_num}'
            else:
                col_name = f'{model} {source_language} to {target_language} {technique}'
            col_names |= {col_name}

            if col_name not in results.columns:
                results[col_name] = ''

            str_date_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

            result = cnv.verify(translated, target_language, problem_id)

            if result['status'] == "Success":
                RichLog.info(f"{solution_file} works ✔")
            else:
                message = f"\n\n/* Error log - appended by evaluation at {str_date_time}:\n\n{result['message']}\n*/"
                solution_file.write_text(translated + message)
                RichLog.info(f"{solution_file} failed")

            results.loc[(problem_id, sol_id), col_name] = result['status']

    for col_name in col_names:
        total     = results[col_name].count()
        succeeded = results[col_name].value_counts().get('Success', 0)
        RichLog.info("For {}:".format(col_name))
        RichLog.info("Overall {}/{} succeeded.".format(succeeded, total))
        RichLog.info("Accuracy {0:.2f}".format(100.0 * succeeded/total))
    
    results.to_csv(results_file.absolute(), sep="\t", mode='w', index=True)
    print("Results saved to", results_file.absolute())

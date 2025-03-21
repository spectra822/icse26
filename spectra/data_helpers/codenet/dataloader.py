from utils.color_logger import RichLog
from utils.progress_bar import ProgressBarFactory

import pandas as pd
import os
import json
from pathlib import Path

class CodeNet:

    codenet_dir = Path(os.environ['CODENET_DIR'])
    meta_dir    = codenet_dir.joinpath('metadata')
    desc_dir    = codenet_dir.joinpath('problem_descriptions')
    io_dir      = codenet_dir.joinpath('derived', 'input_output', 'data')

    def __init__(self, language, split='selected'):

        self.language    = language.lower()
        self.split       = split
        self.len         = None

        split_file = Path(os.path.dirname(__file__)).joinpath(f'splits/{split}_{language}.csv')

        if split == 'selected':
            lines = split_file.read_text().split('\n')
            self.problems  = [line.split(',')[0] for line in lines]
            self.solutions = [line.split(',')[1] for line in lines]
        elif split == 'all':
            self.problems  = None
            self.solutions = None
        else:
            raise NotImplementedError(f"Unknown split {split}")

    def __len__(self):

        if self.len is None:
            RichLog.info(f"Computing size of dataset")
            total_files = 0
            with ProgressBarFactory.get_progress_bar() as p:
                for meta_f in p.track(CodeNet.meta_dir.iterdir(), total=len(list(CodeNet.meta_dir.iterdir()))):
                    if (not meta_f.is_dir()) and (meta_f.name != "problem_list.csv"):
                        df = pd.read_csv(meta_f.absolute())
                        df = df[(df['language'].map(lambda x: x.lower()) == self.language) & (df['problem_id'].isin(self.problems))]
                        total_files += df.shape[0]
            return total_files
        else:
            return self.len

    def iterator(self):

        for meta_f in CodeNet.meta_dir.iterdir():

            if (not meta_f.is_dir()) and (meta_f.name != "problem_list.csv"):

                df = pd.read_csv(meta_f.absolute())
                df = df[(df['language'].map(lambda x: x.lower()) == self.language)]
                if self.problems is not None:
                    df = df[df['problem_id'].isin(self.problems)]
                if self.solutions is not None:
                    df = df[df['submission_id'].isin(self.solutions)]

                paths = ('data/' + df['problem_id'] + '/' + df['language'] + '/' + df['submission_id'] + '.' + df['filename_ext'])

                for path, status in zip(paths, df['status']):
                    path = CodeNet.codenet_dir.joinpath(path)
                    with path.open(mode='r') as f:
                        content = f.read()

                    yield {"content": content, "filename": str(path.absolute()), "accepted": (status == 'Accepted')}

    def problem_iterator(self):

        for problem_id in self.problems:
            description = CodeNet.get_description(problem_id)
            input_data, ground_truth = CodeNet.get_io(problem_id)

            yield {"problem_id": problem_id, "description": description, "input": input_data, "output": ground_truth}
    
    @staticmethod
    def get_description(problem_id):

        desc_file = CodeNet.desc_dir.joinpath(f"{problem_id}.html")
        if not desc_file.exists():
            return None

        return desc_file.read_text()

    @staticmethod
    def get_io(problem_id):

        input_path = CodeNet.io_dir.joinpath(problem_id, 'input.txt')
        output_path = CodeNet.io_dir.joinpath(problem_id, 'output.txt')

        if not input_path.exists() or not output_path.exists():
            return None, None
        
        input_data   = input_path.read_text()
        ground_truth = output_path.read_text()

        return input_data, ground_truth
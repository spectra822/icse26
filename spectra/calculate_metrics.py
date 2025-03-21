import pandas as pd
from pathlib import Path
import functools
from datetime import datetime
import argparse
import re
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Translation Evaluator')
parser.add_argument('-results_file', dest="results_file", default='../results.csv', type=str, help="File to load the raw results from")
args = parser.parse_args()

results = pd.read_csv(args.results_file, sep="\t")

all_configs = set()

for col_name in results.columns:
    parts = col_name.split(' ')
    if len(parts) >= 5:
        if (not "codellama" in col_name) and (not "llama8b" in col_name):
            all_configs.add((parts[0], parts[1], parts[3]))

K = 3

gen_table = pd.DataFrame(columns=['Total'] + [f'pass@{i}' for i in range(1, K+1)])

for (model, source_language, target_language) in all_configs:

    # First compute the baseline pass@k rate
    base_row_name = f"{source_language.capitalize()} to {target_language.capitalize()} {model.capitalize()} baseline"
    base_col_name = f'{model} {source_language} to {target_language} baseline'
    successes = [results[base_col_name + f' {i}'] == "Success" for i in range(0, 4)]
    is_some = [~results[base_col_name + f' {i}'].isna() for i in range(0, 4)]
    gen_table.loc[base_row_name, 'Total'] = functools.reduce((lambda a, b: a | b), is_some).sum()

    for k in range(1, K+1):
        gen_table.loc[base_row_name, f'pass@{k}'] = functools.reduce((lambda a, b: a | b), successes[:k]).sum()
    
    # Next compute the technique's pass@k rate
    technique_order = ['invariant', 'test', 'desc', 'baseline 0']
    method_row_name  = f"{source_language.capitalize()} to {target_language.capitalize()} {model.capitalize()} SpecTra"
    for k in range(1, K+1):
        gen_table.loc[method_row_name, f'pass@{k}'] = 0
    gen_table.loc[method_row_name, 'Total'] = 0
    
    for _, row in results.iterrows():
        col_names = [f'{model} {source_language} to {target_language} {technique}' for technique in technique_order]

        successes = [row[col_name] == "Success" for col_name in col_names if not pd.isnull(row[col_name])]
        if len(successes) == 0:
            continue
        else:
            gen_table.loc[method_row_name, 'Total'] += 1
        for k in range(1, K+1):
            pass_k = functools.reduce((lambda a, b: a or b), successes[:k])
            if pass_k:
                gen_table.loc[method_row_name, f'pass@{k}'] += 1

model_order = ["Gpt4o", "Gpt4", "Claude", "Gpt3", "Gemini", "Llama8b", "Codellama34b", "Granite", "Deepseek"]
language_order = ["Rust", "Go", "Typescript"]
technique_order = ["baseline", "SpecTra"]

def get_indices(x):
    parts = x.split(' ')
    return ' '.join([str(language_order.index(parts[2])), str(model_order.index(parts[3])), str(technique_order.index(parts[4]))])
                  
gen_table = gen_table.sort_index(key=lambda x: x.map(get_indices))

percentage_table = 100 * gen_table.divide(gen_table['Total'], axis="index").astype("float").round(4)

new_table = gen_table.copy(deep=True).drop('Total', axis=1)
for row_name, row in gen_table.iterrows():
    for col_name in [f'pass@{i}' for i in range(1, 4)]:
        value = row[col_name]
        percentage = np.round(100 * float(value) / row['Total'], 1)
        new_table.loc[row_name, col_name] = f'{value} ({percentage}%)'

print(new_table)
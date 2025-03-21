# SPECTRA: Enhancing the Code Translation Ability of Language Models by Generating Multi-Modal Specifications

## Pre-requisites

1. Python 3.10
2. [Node.js](https://nodejs.org/en/download/)
3. [Rust](https://www.rust-lang.org/tools/install)
4. [Go](https://golang.org/doc/install)
5. [GCC](https://gcc.gnu.org/install/)

## Initial Setup

1. We have provided our selected subset of CodeNet as part of this repository. If you would like to run our model on files that are outside of our selected subset, then you can download the full [CodeNet dataset](https://developer.ibm.com/data/project-codenet/). 
   
2. Create a `.env` file with your API keys. As shown below, the `.env` file should contain the following entries:
    ```bash
    # Sample .env file
    OPENAI_API_KEY="your_openai_api_key"
    GOOGLE_API_KEY="your_google_api_key"
    ANTHROPIC_API_KEY="your_anthropic_api_key"

    # Path to CodeNet directory containing subfolders `data`, `derived`, etc.
    # If you are using our provided subset, then you do not need to change this line.
    CODENET_DIR="spectra/data/Project_CodeNet_mini"
    ```
    
3. Install Python requirements with pip
   ```
   pip install -r requirements.txt
   ```

## Running SpecTra

1. If you would like to use our pre-generated specifications, then you can skip this step. Otherwise, run the following commands to generate specs for C and JavaScript.

```bash
python generate_specs_c.py -model gpt4o -src_lang c -dir "data/c_spec_store"
python generate_specs_js.py -model gpt4o -src_lang javascript -dir "data/js_spec_store"
```

2. Then perform translation using the generated specifications.

```bash
# C to Rust
python translate.py -model gpt4o -src-lang c -tgt-lang rust -dir "../results_store" -spec_dir "../c_spec_store"
# C to Go
python translate.py -model gpt4o -src-lang c -tgt-lang go -dir "../results_store" -spec_dir "../c_spec_store"
# Javascript to TypeScript
python translate.py -model gpt4o -src-lang javascript -tgt-lang typescript -dir "../results_store" -spec_dir "../js_spec_store"
```

3. Next, evaluate the generated translations.

```bash
python evaluate.py -dir "../results_store" -results_file ../results.csv
```

4. Finally, run our metrics script to generate the tables in the paper.
```bash
python calculate_metrics.py -results_file ../results.csv
```

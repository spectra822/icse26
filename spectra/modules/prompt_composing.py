import os
from pathlib import Path

from utils import wrap_format


def compose_lang_to_lang(code, src_lang, tgt_lang, input_data, ground_truth):
    
    prompt = ""
    prompt += f"Here is a {src_lang.capitalize()} program:\n\n"
    prompt += wrap_format(code.strip(), src_lang)
    prompt += "\n"
    if input_data and ground_truth:
        prompt += f"Here is a test case for the {src_lang.capitalize()} program:\n\n"
        prompt += "Input:\n"
        prompt += input_data
        prompt += "\n\nOutput:\n"
        prompt += ground_truth
        prompt += "\n\n"
        prompt += f"You are an expert {tgt_lang.capitalize()} developer. Convert this {src_lang.capitalize()} program into {tgt_lang.capitalize()} such that the Rust code passes the given test case.  Generate only code, without any accompanying messages or text."
    else:
        prompt += f"You are an expert {tgt_lang.capitalize()} developer. Convert this {src_lang.capitalize()} program into {tgt_lang.capitalize()}. Generate only code, without any accompanying messages or text."

    if "Precondition:" in code or "Postcondition:" in code:
        prompt += " Additionally, if a function has a precondition or postcondition, make sure that the corresponding function in the Rust code also satisfies the same conditions."

    return prompt


def compose_code_to_test(code, lang="c"):

    testgen_prompt = Path(os.path.dirname(__file__)).joinpath(f'../{lang}_prompt_templates/testgen_prompt.txt').read_text()

    prompt = ""
    prompt += testgen_prompt
    prompt += f'''
Here is another {lang.capitalize()} program:
{wrap_format(code.strip(), lang)}
Similar to the above example, generate a test case for this program, with a sample input and the expected output.

You can generate whatever intermediate text you want, but the final test case should be in the following format, as in the previous example:
--Generated test case--
Sample Input:
...

Expected Output:
...
--End of test case--
'''
    
    return prompt


def compose_code_to_desc(code, lang, input_data, ground_truth):

    if lang not in ["c", "c++", "javascript"]:
        raise NotImplementedError("Unsupported language")
    
    sketch_prompt = Path(os.path.dirname(__file__)).joinpath(f'../{lang}_prompt_templates/desc_only_sketch.txt').read_text()

    prompt = ""
    prompt = sketch_prompt
    prompt += "\n"
    prompt += f"Here is another {lang.capitalize()} program:\n\n"
    prompt += wrap_format(code.strip(), lang)
    prompt += "\n"

    if input_data and ground_truth:
        prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        prompt += "Input:\n"
        prompt += input_data
        prompt += "\n\nOutput:\n"
        prompt += ground_truth
        prompt += "\n\n"

    prompt += f'''
Similar to the previous example, generate a sketch of the {lang.capitalize()} program, in the following format.
```
// Global variables
<Global variable declarations>

// <Function 1 description>
<Function1 signature>
    <Calls to other functions, if any>

// <Function 2 description>
<Function2 signature>
    <Calls to other functions, if any>

...
```
Each function should have its signature and a brief description of what it does as a comment above it. Mention global variables if any.
Mention the names of other functions that each function calls. However, *do not* include any code from the body of any of the functions.
'''

    return prompt


def compose_code_to_invariant(code, lang, input_data, ground_truth):

    if lang not in ["c", "c++"]:
        raise NotImplementedError("Unsupported language")

    invariant_prompt = Path(os.path.dirname(__file__)).joinpath(f'../{lang}_prompt_templates/postcondition.txt').read_text()

    prompt = ""
    prompt = invariant_prompt
    prompt += "\n"
    prompt += f"Here is another {lang.capitalize()} program:\n\n"
    prompt += wrap_format(code.strip(), lang)
    prompt += "\n"
    if input_data and ground_truth:
        prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        prompt += "Input:\n"
        prompt += input_data
        prompt += "\n\nOutput:\n"
        prompt += ground_truth
        prompt += "\n\n"
        prompt += f'''
Similar to the above example, write a precondition and a postcondition for each function in this {lang.capitalize()} program, in the following format.
Note that the `main` function has the input and output formats also mentioned. These should be precise and sufficient to understand the exact input and output format of the program, including any spaces, linebreaks, etc.
```
<Function1 signature>
    // Precondition: <condition>
    // Postcondition: <condition>

<Function2 signature>
    // Precondition: <condition>
    // Postcondition: <condition>

...

<main function signature>
    // Input format: <format>
    // Output format: <format>
    // Precondition: <condition>
    // Postcondition: <condition>

Although the preconditions and postconditions should be less complex than the function itself, they should not be trivial. They should encapsulate an aspect of the function without reproducing the function itself.
For variables, use only the function input parameters (if any), any variables that are taken as input from STDIN, global variables, and a hypothetical return value, which we'll assume is stored in a variable `return_val`. 

Make sure to generate your output in exactly the format shown above. Write each function signature, followed by the precondition and postcondition as comments with no extra formatting or markup.
'''
    return prompt


def compose_desc_to_code(desc, lang, test_input, test_output):

    new_prompt = ""
    new_prompt += f"The following is a sketch of a {lang.capitalize()} program, where each function has its signature and a brief description of what it does. "
    new_prompt += "Global variables, if any, are indicated.\n\n"
    new_prompt += desc
    new_prompt += "\n\n"

    if test_input and test_output:
        new_prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        new_prompt += "Input:\n"
        new_prompt += test_input
        new_prompt += "\n\nOutput:\n"
        new_prompt += test_output
        new_prompt += "\n\n"
        new_prompt += f"Please complete the {lang.capitalize()} program using this sketch such that it passes the above test case. "
    else:
        new_prompt += f"Please complete the {lang.capitalize()} program using this sketch. "
        
    new_prompt += f"Fill in each of these functions with a complete implementation. Do not create any new functions - the functions in the {lang.capitalize()} program must be the same as the functions in the sketch. "
    new_prompt += "Give me the whole program in one shot, not piece by piece.\n\n"
    
    return new_prompt


def compose_invariant_to_code(invariant, lang, test_input, test_output):

    new_prompt = ""
    new_prompt += f"The following is a sketch of a {lang.capitalize()} program, where each function has its signature, along with a precondition and postcondition.\n\n"
    new_prompt += invariant
    new_prompt += "\n\n"

    if test_input and test_output:
        new_prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        new_prompt += "Input:\n"
        new_prompt += test_input
        new_prompt += "\n\nOutput:\n"
        new_prompt += test_output
        new_prompt += "\n\n"

    new_prompt += f"Please complete the {lang.capitalize()} program such that each function obeys the provided preconditions and postconditions. Also note that the program must read from STDIN and write to STDOUT in the provided input and output format. "

    if test_input and test_output:
        new_prompt += "Make sure that the code passes the above test case. Pay close attention to whitespaces in the output and make sure that your program does not print any extra characters. "
        
    new_prompt += f"Fill in each of the functions with a complete implementation. Do not create any new functions - the functions in the {lang.capitalize()} program must be the same as the functions in the sketch."
    new_prompt += "Give me the whole program in one shot, not piece by piece.\n\n"
    
    return new_prompt
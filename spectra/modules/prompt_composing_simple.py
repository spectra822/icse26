import os
from pathlib import Path

from utils import wrap_format

def simple_compose_code_to_desc(code, lang, input_data, ground_truth):

    if lang not in ["c", "c++", "javascript"]:
        raise NotImplementedError("Unsupported language")
    
    prompt = ""
    prompt += wrap_format(code.strip(), lang)
    prompt += "\n"
    
    if input_data and ground_truth:
        prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        prompt += "Input:\n"
        prompt += input_data
        prompt += "\n\nOutput:\n"
        prompt += ground_truth
        prompt += "\n"
    prompt += '''
Partition this program into multiple contiguous segments such that each segment is cohesive.
For example, a segment can be a single function, or a group of variable declarations, etc.
The union of all these segments should cover the entire program.
Then, before each segment, insert a comment describing what that segment does.
'''
    return prompt


def simple_compose_code_to_invariant(code, lang, input_data, ground_truth):

    if lang not in ["c", "c++", "javascript"]:
        raise NotImplementedError("Unsupported language")
    
    prompt = ""
    prompt += wrap_format(code.strip(), lang)
    prompt += "\n"
    
    if input_data and ground_truth:
        prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        prompt += "Input:\n"
        prompt += input_data
        prompt += "\n\nOutput:\n"
        prompt += ground_truth
        prompt += "\n"
    prompt += '''
Partition this program into multiple contiguous segments such that each segment is cohesive.
For example, a segment can be a single function, or a group of variable declarations, etc.
The union of all these segments should cover the entire program.

Then, before each segment, write a Precondition and a Postcondition for that segment.
Although the preconditions and postconditions should be less complex than the segment's code itself, they should not be trivial.
They should encapsulate an aspect of that segment's code without reproducing the code itself.

Further, if a particular segment takes input from the user or produces output, mention the input and output format in the comments.
These should be precise and sufficient to understand the exact input and output format of the program, including any spaces, linebreaks, etc.
'''
    return prompt


def simple_compose_desc_to_code(desc, lang, test_input, test_output):

    new_prompt = ""
    new_prompt += f"Here is the outline of a {lang.capitalize()} program:\n\n"
    new_prompt += wrap_format(desc.strip(), lang)
    new_prompt += "\n\n"

    if test_input and test_output:
        new_prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        new_prompt += "Input:\n"
        new_prompt += test_input
        new_prompt += "\n\nOutput:\n"
        new_prompt += test_output
        new_prompt += "\n\n"
        new_prompt += f"Using the comments, fill in the {lang.capitalize()} program such that it passes the above test case. "
    else:
        new_prompt += f"Using the comments, fill in the {lang.capitalize()} program. "
        
    new_prompt += f"Fill in code wherever there is a `<insert code here>`."
    
    return new_prompt


def simple_compose_invariant_to_code(desc, lang, test_input, test_output):

    new_prompt = ""
    new_prompt += f"Here is the outline of a {lang.capitalize()} program:\n\n"
    new_prompt += wrap_format(desc.strip(), lang)
    new_prompt += "\n\n"

    if test_input and test_output:
        new_prompt += f"Here is a test case for the {lang.capitalize()} program:\n\n"
        new_prompt += "Input:\n"
        new_prompt += test_input
        new_prompt += "\n\nOutput:\n"
        new_prompt += test_output
        new_prompt += "\n\n"
        new_prompt += f"Using the comments, fill in the {lang.capitalize()} program such that it passes the above test case. "
    else:
        new_prompt += f"Using the comments, fill in the {lang.capitalize()} program. "
        
    new_prompt += '''
Fill in code wherever there is a `<insert code here>`.
Make sure that each block of code obeys the preconditions and postconditions mentioned above it as a comment.
The code should take input from the user and produce output in the format mentioned in the comments.
''' 
    return new_prompt
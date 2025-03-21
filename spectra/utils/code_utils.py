import numpy as np
import re

# If you add a new function or variable to this file, make sure to add it to the __all__ list at the bottom of the file

lang_to_extension = {"c": "c",
                     "c++": "cpp",
                     "rust": "rs",
                     "java": "java",
                     "python": "py",
                     "go": "go",
                     "javascript": "js",
                     "typescript": "ts"}

def wrap_format(code: str, lang: str):
    return f'```{lang.lower()}\n{code}\n```'

def multiline_to_singleline(code):
    # Find all multiline comments in the code and replace them with single line comments
    pattern = re.compile("(/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)")
    for match in pattern.findall(code):
        match = match[0]
        code = code.replace(match, "//" + match[2:-2].replace("\n", "\n//") + '\n')
    return code

def strip_noncode(text, retain_markdown=True):
    # Remove all non-code parts from the text
    code_parts = []
    in_code = False
    for line in text.split("\n"):
        if "```" in line:
            in_code = not in_code
            if retain_markdown:
                code_parts.append(line)
            continue
        if in_code:
            code_parts.append(line)
    return "\n".join(code_parts)

def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def cosine_similarity(a, b):
    return np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b))

def remove_non_comments(code):
    new_lines = []
    first_in_block = False
    for line in code.split("\n"):
        if line.strip().startswith("//"):
            new_lines += [line]
            first_in_block = True
        else:
            if first_in_block:
                # Extract the whitespaces at the start of the line
                whitespace = re.match(r"^\s*", line).group()
                new_lines += [f"{whitespace}<insert code here>"]
                first_in_block = False
    return "\n".join(new_lines)


__all__ = ["wrap_format", "lang_to_extension", "multiline_to_singleline", "strip_noncode", "comment_remover", "cosine_similarity", "remove_non_comments"]
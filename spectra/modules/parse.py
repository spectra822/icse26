import re
from utils import RichLog, multiline_to_singleline

def parse_test(gpt_output: str):

    if "--Generated test case--" not in gpt_output or "--End of test case--" not in gpt_output:
        return None, None
    
    gpt_output = gpt_output[gpt_output.index("--Generated test case--") + len("--Generated test case--"):].strip()
    gpt_output = gpt_output[:gpt_output.index("--End of test case--")].strip()

    if "Sample Input:" not in gpt_output or "Expected Output:" not in gpt_output:
        return None, None
    
    sample_input = gpt_output[gpt_output.index("Sample Input:") + len("Sample Input:"):gpt_output.index("Expected Output:")].strip()
    expected_output = gpt_output[gpt_output.index("Expected Output:") + len("Expected Output:"):].strip()

    return sample_input, expected_output

def merge_desc_code(desc, code, lang):
    # desc contains function signatures with comments above them
    # Take those comments and add them to the code as comments
    # Then return the merged code

    if lang not in ["c", "c++", "rust", "go"]:
        raise NotImplementedError("Unsupported language")

    desc_lines = desc.split("\n")
    code_lines = code.split("\n")

    succeeded = False
    current_comment = []
    for line in desc_lines:
        if line.strip().startswith("//"):
            current_comment.append(line)
        elif len(line.strip()) > 0:
            pattern = r'(\w+\s+)?\w+\s*\([^)]*\)(?=\s*)'
            if re.match(pattern, line.strip()):
                signature = line.strip()
                # Find the function in the code
                for i, code_line in enumerate(code_lines):
                    if signature in code_line:
                        # Insert the comment above the function
                        code_lines.insert(i, "\n".join(current_comment))
                        if len(current_comment) > 0:
                            succeeded = True
                        current_comment = []
                        break

    if not succeeded:
        RichLog.warn("Failed to merge descriptions with the code. Concatenating it below")
        code_lines += ["/*"]
        code_lines += desc_lines
        code_lines += ["*/"]

    return "\n".join(code_lines)

def merge_invariant_code(invariant, code, lang):
    # invariant contains function signatures with comments below them
    # Take those comments and add them to the code as comments
    # Then return the merged code

    if lang not in ["c", "c++", "rust", "go"]:
        raise NotImplementedError("Unsupported language")

    invariant_lines = invariant.split("\n")
    code_lines = code.split("\n")

    # Succeeded in finding at least one invariant and merging it with the code
    succeeded = False

    found = False
    found_at = -1
    current_comment = []

    for line in invariant_lines:

        if not found:
            pattern = r'(\w+\s+)?\w+\s*\([^)]*\)(?=\s*)'
            if re.match(pattern, line.strip()):
                signature = line.strip()
                # Find the signature in the code
                for i, code_line in enumerate(code_lines):
                    if signature in code_line:
                        found = True
                        found_at = i
                        break
        else:
            if (not line.strip().startswith("//")) or (len(line.strip()) == 0) or (line.strip() == "*/") or (line.strip() == "```"):
                code_lines.insert(found_at+1, "\n".join(current_comment))
                if len(current_comment) > 0:
                    succeeded = True
                found = False
                found_at = -1
                current_comment = []
            else:
                # if not line.strip().startswith("//"):
                #     line = "\t// " + line
                current_comment.append(line)
    
    # For the edge case where the last function has an invariant
    if found:
        code_lines.insert(found_at+1, "\n".join(current_comment))
        if len(current_comment) > 0:
                    succeeded = True
    
    if not succeeded:
        RichLog.warn("Failed to merge invariants with the code. Concatenating it below")
        code_lines += ["/*"]
        code_lines += invariant_lines
        code_lines += ["*/"]
    
    return "\n".join(code_lines)

def parse_reply(reply, messages, lang):

    reply_head, reply_body, reply_tail = "", reply, ""

    # If there is a ```{lang} anywhere in the code, remove everything before it
    if f"```{lang}" in reply_body:
        reply_head = reply_body[:reply_body.index(f"```{lang}") + len(f"```{lang}")]
        reply_body = reply_body[reply_body.index(f"```{lang}") + len(f"```{lang}"):]

    # If there is a ``` anywhere in the code, remove everything after it
    if "```" in reply_body:
        reply_tail  = reply_body[reply_body.index("```"):]
        reply_body  = reply_body[:reply_body.index("```")]
    
    # To account for nested multiline comments
    reply_body = multiline_to_singleline(reply_body)

    intermediate_messages = ""
    for message in messages:
        if message["role"] == "assistant":
            content = multiline_to_singleline(message["content"])
            intermediate_messages += f"/*\nAssistant:\n{content}\n*/\n"
        elif message["role"] == "user":
            if lang in ["c", "c++", "go", "javascript", "typescript"]:
                content = multiline_to_singleline(message["content"])
            else:
                content = message["content"]
            intermediate_messages += f"/*\nUser:\n{content}\n*/\n"

    reply_to_write = f"{intermediate_messages}/*\n{reply_head}\n*/\n{reply_body}\n/*\n{reply_tail}\n*/"

    return reply_to_write
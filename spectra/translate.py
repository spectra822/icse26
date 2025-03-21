import re, argparse, os
from pathlib import Path

from data_helpers import CodeNet, CodeNetVerifier
from utils import RichLog, lang_to_extension, comment_remover
from models import get_model_from_name, ModelException
from modules import compose_lang_to_lang, parse_reply


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
            pattern = r"(\w+\s+)?\w+\s*\([^)]*\)(?=\s*)"
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
        RichLog.warn(
            "Failed to merge descriptions with the code. Concatenating it below"
        )
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
            pattern = r"(\w+\s+)?\w+\s*\([^)]*\)(?=\s*)"
            if re.match(pattern, line.strip()):
                signature = line.strip()
                # Find the signature in the code
                for i, code_line in enumerate(code_lines):
                    if signature in code_line:
                        found = True
                        found_at = i
                        break
        else:
            if (
                (not line.strip().startswith("//"))
                or (len(line.strip()) == 0)
                or (line.strip() == "*/")
                or (line.strip() == "```")
            ):
                code_lines.insert(found_at + 1, "\n".join(current_comment))
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
        code_lines.insert(found_at + 1, "\n".join(current_comment))
        if len(current_comment) > 0:
            succeeded = True

    if not succeeded:
        RichLog.warn("Failed to merge invariants with the code. Concatenating it below")
        code_lines += ["/*"]
        code_lines += invariant_lines
        code_lines += ["*/"]

    return "\n".join(code_lines)


def generate_write_verify(
    save_path,
    code,
    src_lang,
    tgt_lang,
    model,
    input_data,
    ground_truth,
    top_k=1,
    gen_input_data=None,
    gen_ground_truth=None,
):

    if top_k != 1:
        temperature = 0.6 if "Claude" in type(model).__name__ else 0.3
        RichLog.info(
            f"Multiple completions requested. Setting temperature to {temperature}"
        )
    else:
        temperature = 0

    prompt = compose_lang_to_lang(
        code, src_lang, tgt_lang, gen_input_data, gen_ground_truth
    )

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": prompt}]

    gen = model.gen(messages, temperature=temperature, top_k=top_k)
    cnv = CodeNetVerifier()

    passed = False
    selected_code = None
    if len(gen) > 1:
        if len(set(gen)) != len(gen):
            RichLog.warn(
                f"Total completions: {len(gen)}, unique completions: {len(set(gen))}"
            )
        for i, g in enumerate(gen):
            g = g.strip()
            reply_to_write = parse_reply(g, messages, tgt_lang)
            new_save_path = save_path.with_stem(save_path.stem + f"-{i}")
            new_save_path.write_text(reply_to_write)
            RichLog.info(f"Wrote generation to {new_save_path.absolute()}")
            if input_data and ground_truth and (not passed):
                valgrind = True if src_lang in ["c", "c++"] else False
                result = cnv.verify_with_custom_test(
                    reply_to_write,
                    tgt_lang,
                    input_data,
                    ground_truth,
                    valgrind=valgrind,
                    coverage=False,
                )
                if result["status"] == "Success":
                    passed = True
                    selected_code = reply_to_write
    else:
        gen = gen[0].strip()
        reply_to_write = parse_reply(gen, messages, tgt_lang)
        save_path.write_text(reply_to_write)
        RichLog.info(f"Wrote generation to {save_path.absolute()}")
        if input_data and ground_truth:
            valgrind = True if src_lang in ["c", "c++"] else False
            result = cnv.verify_with_custom_test(
                reply_to_write,
                tgt_lang,
                input_data,
                ground_truth,
                valgrind=valgrind,
                coverage=False,
            )
            if result["status"] == "Success":
                passed = True
                selected_code = reply_to_write

    return passed, selected_code


def load_invariant(problem_id, sol_id, spec_dir):
    invariant_path = Path(f"{spec_dir}/{problem_id}/{sol_id}_invariant.txt")
    if not invariant_path.exists():
        return None
    else:
        RichLog.info(f"Loaded invariant from {invariant_path.absolute()}")
        return invariant_path.read_text().strip()


def load_test(problem_id, sol_id, spec_dir):

    test_path = Path(f"{spec_dir}/{problem_id}/{sol_id}_test.txt")
    if not test_path.exists():
        return None, None

    contents = test_path.read_text()

    sample_input = contents[
        contents.index("Input:") + len("Input:") : contents.index("Output:")
    ].strip()
    expected_output = contents[contents.index("Output:") + len("Output:") :].strip()

    RichLog.info(f"Loaded test from {test_path.absolute()}")

    return sample_input, expected_output


def load_desc(problem_id, sol_id, spec_dir):

    desc_path = Path(f"{spec_dir}/{problem_id}/{sol_id}_desc.txt")
    if not desc_path.exists():
        return None
    else:
        RichLog.info(f"Loaded description from {desc_path.absolute()}")
        return desc_path.read_text().strip()


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Perform translation using specs")
    parser.add_argument(
        "-dir",
        dest="dir",
        required=True,
        type=str,
        help="Directory to write the generated files",
    )
    parser.add_argument(
        "-spec_dir",
        dest="spec_dir",
        required=True,
        type=str,
        help="Directory containing the generated specs",
    )
    parser.add_argument(
        "-overwrite",
        dest="overwrite",
        action="store_true",
        help="Overwrite existing files",
    )
    parser.add_argument(
        "-model",
        dest="model",
        default="gpt4o",
        type=str,
        help="Model to use for translation [gpt4o|gpt4|gpt3|gemini|claude]",
    )
    parser.add_argument(
        "-src_lang", dest="src_lang", default="c", type=str, help="Source language"
    )
    parser.add_argument(
        "-tgt_lang", dest="tgt_lang", default="rust", type=str, help="Target language"
    )
    parser.add_argument(
        "-no_merge",
        dest="merge",
        action="store_false",
        help="Don't merge the generated specs with the provided code",
    )
    parser.add_argument(
        "-nobaseline",
        dest="baseline",
        action="store_false",
        help="Don't do baseline translation",
    )
    parser.add_argument(
        "-noinvariant",
        dest="invariant",
        action="store_false",
        help="Don't use invariants",
    )
    parser.add_argument(
        "-notests", dest="tests", action="store_false", help="Don't use tests"
    )
    parser.add_argument(
        "-nodesc", dest="desc", action="store_false", help="Don't use descriptions"
    )
    args = parser.parse_args()

    if args.src_lang == "javascript" and args.merge:
        RichLog.warn(
            "Merging specs with code is not required for JavaScript. Please rerun with -no_merge"
        )
        exit(1)

    if args.src_lang == "c" and not args.merge:
        RichLog.warn(
            "Merging specs with code is required for C. Please rerun without -no_merge"
        )
        exit(1)

    model = get_model_from_name(args.model)

    save_dir = Path(os.path.dirname(__file__)).joinpath(args.dir)
    gen_test_dir = Path(os.path.dirname(__file__)).joinpath("../generated_tests")
    tgt_ext = lang_to_extension[args.tgt_lang]

    if not save_dir.exists():
        save_dir.mkdir()

    success = {"baseline": 0, "invariant": 0, "test": 0, "desc": 0}
    fail = 0
    no_tests = 0

    test_dataset = CodeNet(args.src_lang, "selected")
    cnv = CodeNetVerifier()

    for data in test_dataset.iterator():
        problem_id = data["filename"].split("/")[-3]
        solution_file = data["filename"].split("/")[-1]
        sol_id, sol_ext = solution_file.split(".")

        if not (save_dir / problem_id).exists():
            (save_dir / problem_id).mkdir()

        save_path0 = save_dir.joinpath(
            f"{problem_id}/{sol_id}_baseline_{args.src_lang}-gen0_{args.tgt_lang}_{args.model}.{tgt_ext}"
        )
        save_path1 = save_dir.joinpath(
            f"{problem_id}/{sol_id}_baseline_{args.src_lang}-gen1_{args.tgt_lang}_{args.model}.{tgt_ext}"
        )
        save_path2 = save_dir.joinpath(
            f"{problem_id}/{sol_id}_baseline_{args.src_lang}-gen2_{args.tgt_lang}_{args.model}.{tgt_ext}"
        )
        save_path3 = save_dir.joinpath(
            f"{problem_id}/{sol_id}_baseline_{args.src_lang}-gen3_{args.tgt_lang}_{args.model}.{tgt_ext}"
        )

        RichLog.info(f"Processing {problem_id}/{sol_id}")

        try:
            original_code = data["content"]
            RichLog.info("Loading provided test cases")
            input_data, ground_truth = CodeNet.get_io(problem_id)

            result = cnv.verify(original_code, args.src_lang, problem_id)
            if result["status"] != "Success":
                print(
                    f"Skipping {data['filename']} because it doesn't solve the problem"
                )
                continue

            if not input_data or not ground_truth:
                RichLog.warn("Failed to generate or load test cases. Skipping.")
                no_tests += 1
                continue

            if args.baseline:
                # Baseline case
                RichLog.info("Trying plain translation")
                if (not args.overwrite) and all(
                    [
                        save_path0.with_stem(save_path0.stem + f"-{i}").is_file()
                        for i in range(4)
                    ]
                ):
                    RichLog.info(f"Already generated {save_path0}. Skipping")
                else:
                    passed, gen_code = generate_write_verify(
                        save_path0,
                        original_code,
                        args.src_lang,
                        args.tgt_lang,
                        model,
                        input_data,
                        ground_truth,
                        top_k=4,
                    )
                    RichLog.info("Succeeded" if passed else "Failed")
                    if passed:
                        assert gen_code is not None
                        success["baseline"] += 1

            if args.invariant:
                RichLog.info("Trying with invariants")
                # Generate invariant (optionally using self-consistency)
                invariant = load_invariant(problem_id, sol_id, args.spec_dir)
                if invariant is None:
                    RichLog.warn(
                        "Failed to generate a self-consistent invariant. Moving on"
                    )
                else:
                    if args.merge:
                        code_with_invariants = merge_invariant_code(
                            invariant, original_code, args.src_lang
                        )
                    else:
                        code_with_invariants = invariant
                    # src+invariant-->target
                    if (not args.overwrite) and save_path1.is_file():
                        RichLog.info(f"Already generated {save_path1}. Skipping")
                    else:
                        passed, gen_code = generate_write_verify(
                            save_path1,
                            code_with_invariants,
                            args.src_lang,
                            args.tgt_lang,
                            model,
                            input_data,
                            ground_truth,
                            top_k=1,
                        )
                        RichLog.info("Succeeded" if passed else "Failed")
                        if passed:
                            assert gen_code is not None
                            success["invariant"] += 1

            if args.tests:
                RichLog.info("Trying with tests")
                gen_input_data, gen_ground_truth = load_test(
                    problem_id, sol_id, args.spec_dir
                )
                if gen_input_data is None or gen_ground_truth is None:
                    RichLog.warn("Failed to generate test cases. Moving on")
                else:
                    # result = cnv.verify_with_custom_test(original_code, args.src_lang, gen_input_data, gen_ground_truth, eof=True, valgrind=True, coverage=True)
                    # if result['status'] != "Success":
                    #     RichLog.warn("This test isn't correct")
                    #     import pdb; pdb.set_trace()
                    # else:
                    #     RichLog.info("This test is correct")
                    # src+test-->target
                    if (not args.overwrite) and save_path2.is_file():
                        RichLog.info(f"Already generated {save_path2}. Skipping")
                    else:
                        passed, gen_code = generate_write_verify(
                            save_path2,
                            original_code,
                            args.src_lang,
                            args.tgt_lang,
                            model,
                            input_data,
                            ground_truth,
                            top_k=1,
                            gen_input_data=gen_input_data,
                            gen_ground_truth=gen_ground_truth,
                        )
                        RichLog.info("Succeeded" if passed else "Failed")
                        if passed:
                            assert gen_code is not None
                            success["test"] += 1

            if args.desc:
                RichLog.info("Trying with descriptions")
                # Generate description (optionally using self-consistency)
                desc = load_desc(problem_id, sol_id, args.spec_dir)
                if desc is None:
                    RichLog.warn(
                        "Failed to generate a self-consistent description. Moving on"
                    )
                else:
                    if args.merge:
                        code_with_desc = merge_desc_code(
                            desc, original_code, args.src_lang
                        )
                    else:
                        code_with_desc = desc
                    # src+desc-->target
                    if (not args.overwrite) and save_path3.is_file():
                        RichLog.info(f"Already generated {save_path3}. Skipping")
                    else:
                        passed, gen_code = generate_write_verify(
                            save_path3,
                            code_with_desc,
                            args.src_lang,
                            args.tgt_lang,
                            model,
                            input_data,
                            ground_truth,
                            top_k=1,
                        )
                        RichLog.info("Succeeded" if passed else "Failed")
                        if passed:
                            assert gen_code is not None
                            success["desc"] += 1

        except ModelException as e:
            print(f"Error: {e}")
            print("Skipping this attempt")
            continue

    # Print success and failure statistics
    RichLog.info("Successes:")
    for key, value in success.items():
        RichLog.info(f"{key}: {value}")
    RichLog.info(f"Failures: {fail}")
    RichLog.info(f"No tests: {no_tests}")

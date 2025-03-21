import argparse, os
from pathlib import Path
import pandas as pd

from data_helpers import CodeNet, CodeNetVerifier
from utils import RichLog, strip_noncode
# from utils import comment_remover, cosine_similarity
from models import get_model_from_name, ModelException
from modules import compose_code_to_test, compose_code_to_desc, compose_code_to_invariant, compose_desc_to_code, compose_invariant_to_code
from modules import parse_reply, parse_test


def select_test_case(test_cases, code, lang="c", num_to_select=1):

    cnv = CodeNetVerifier()

    test_cases = list(set(test_cases)) # To weed out duplicates
    correct_output   = []
    incorrect_output = []

    first_correct, first_incorrect = -1, -1

    valgrind = (lang == "c")

    for i, (sample_input, expected_output) in enumerate(test_cases):
        result = cnv.verify_with_custom_test(code, lang, sample_input, expected_output, eof=True, valgrind=valgrind, coverage=True)
        if result['status'] == "Success":
            correct_output += [((sample_input, expected_output), result['coverage'])]
            if first_correct == -1:
                first_correct = i
        elif (result['status'] == "Incorrect Output") and (len(result["stdout"]) != 0) and (len(result["stdout"]) < 1000):
            incorrect_output += [((sample_input, result['stdout']), result['coverage'])]
            if first_incorrect == -1:
                first_incorrect = i
    
    if len(correct_output) > 0:
        correct_output = sorted(correct_output, key=lambda x: x[1], reverse=True)
        print(f"Generated {len(correct_output)} test cases with correct output. The best coverage was {correct_output[0][1]}")
    
    if len(incorrect_output) > 0:
        incorrect_output = sorted(incorrect_output, key=lambda x: x[1], reverse=True)
        print(f"Generated {len(incorrect_output)} test cases with incorrect output. The best coverage was {incorrect_output[0][1]}")
    
    if len(correct_output) == 0 and len(incorrect_output) == 0:
        print("Failed to generate a succesful test case")

    # Concat correct_output and incorrect_output
    test_cases      = correct_output + incorrect_output
    selected_tests  = [test_case[0] for test_case in test_cases]
    coverages       = [test_case[1] for test_case in test_cases]

    return {'selected_tests':   selected_tests[:num_to_select],
            'coverages':        coverages[:num_to_select],
            'first_correct':    first_correct,
            'first_incorrect':  first_incorrect
        }


def generate_tests(code, lang, model, num_tests=10, self_consistency=True):

    testgen_prompt = compose_code_to_test(code, lang)

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": testgen_prompt}]

    testgen = model.gen(messages, temperature=0.6, top_k=num_tests)
    all_tests = [parse_test(test.strip()) for test in testgen]
    all_tests = [(inp, out) for inp, out in all_tests if (inp, out) != (None, None)]
    metadata  = dict()
    if self_consistency:
        metadata = select_test_case(all_tests, code, lang, num_to_select=1)
        selected_tests = metadata['selected_tests']
        metadata.pop('selected_tests')
        if len(selected_tests) > 0:
            metadata['coverage'] = metadata['coverages'][0]
            metadata.pop('coverages')
            input_data, ground_truth = selected_tests[0]
        else:
            metadata.pop('coverages')
            metadata['coverage'] = None
            input_data, ground_truth = None, None
    else:
        if len(all_tests) == 0:
            input_data, ground_truth = None, None
        else:
            input_data, ground_truth = all_tests[0]
    
    if input_data and ground_truth:
        RichLog.info("Generated test cases")
    else:
        RichLog.warn("Failed to generate test cases")
    
    return metadata, (input_data, ground_truth)

def reverse_gen_desc(desc, lang, model, input_data, ground_truth):
    
    desc_to_code_prompt = compose_desc_to_code(desc, lang, input_data, ground_truth)

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": desc_to_code_prompt}]

    code = model.gen(messages, temperature=0, top_k=1)
    code = code[0].strip()
    reply = parse_reply(code, messages, lang)
    RichLog.info("Reverse-generated code from description")

    return reply

def reverse_gen_invariant(invariant, lang, model, input_data, ground_truth):
    
    invariant_to_code_prompt = compose_invariant_to_code(invariant, lang, input_data, ground_truth)

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": invariant_to_code_prompt}]

    code = model.gen(messages, temperature=0, top_k=1)
    code = code[0].strip()
    reply = parse_reply(code, messages, lang)
    RichLog.info("Reverse-generated code from invariants")

    return reply

def generate_desc(code, lang, model, input_data, ground_truth, self_consistency=False, num_candidates=6):

    cnv = CodeNetVerifier()
    desc_prompt = compose_code_to_desc(code, lang, input_data, ground_truth)

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": desc_prompt}]

    selected_index = -1

    if self_consistency:
        descriptions = model.gen(messages, temperature=0.6, top_k=num_candidates)
        similarities, selected_desc = [], None
        for i, desc in enumerate(descriptions):
            desc = strip_noncode(desc)
            RichLog.info(f"Attempt {i+1} of {len(descriptions)}")
            code_guess = reverse_gen_desc(desc, lang, model, None, None)

            # code_embedding = get_embedding(comment_remover(code))
            # guess_embedding = get_embedding(comment_remover(code_guess))
            # similarity = cosine_similarity(code_embedding, guess_embedding)
            # similarities += [similarity]

            if input_data and ground_truth:
                valgrind = True if lang in ["c", "c++"] else False
                result = cnv.verify_with_custom_test(code_guess, lang, input_data, ground_truth, valgrind=valgrind, coverage=False)
                if result['status'] == "Success":
                    selected_desc = desc
                    selected_index = i
                    RichLog.info("Found a self-consistent description")
                    break

        if selected_desc is None:
            RichLog.warn("Failed to find a self-consistent description.")
            return None, None
            # selected_desc = descriptions[np.argmax(similarities)]
    else:
        selected_desc = model.gen(messages, temperature=0, top_k=1)
        selected_desc = selected_desc[0].strip()
        selected_desc = strip_noncode(selected_desc)
        RichLog.info("Generated NL descriptions")

    return selected_index, selected_desc

def generate_invariant(code, lang, model, input_data, ground_truth, self_consistency=False, num_candidates=6):
        
    cnv = CodeNetVerifier()
    invariant_prompt = compose_code_to_invariant(code, lang, input_data, ground_truth)

    messages = [{"role": "system", "content": "You are a intelligent code assistant."}]
    messages += [{"role": "user", "content": invariant_prompt}]

    selected_index = -1

    if self_consistency:
        invariants = model.gen(messages, temperature=0.6, top_k=num_candidates)
        similarities, selected_invariant = [], None
        for i, invariant in enumerate(invariants):
            invariant = strip_noncode(invariant)
            RichLog.info(f"Attempt {i+1} of {len(invariants)}")
            code_guess = reverse_gen_invariant(invariant, lang, model, None, None)

            # code_embedding = get_embedding(comment_remover(code))
            # guess_embedding = get_embedding(comment_remover(code_guess))
            # similarity = cosine_similarity(code_embedding, guess_embedding)
            # similarities += [similarity]

            if input_data and ground_truth:
                valgrind = True if lang in ["c", "c++"] else False
                result = cnv.verify_with_custom_test(code_guess, lang, input_data, ground_truth, valgrind=valgrind, coverage=False)
                if result['status'] == "Success":
                    selected_invariant = invariant
                    selected_index = i
                    RichLog.info("Found a self-consistent invariant")
                    break

        if selected_invariant is None:
            RichLog.warn("Failed to find a self-consistent invariant.")
            return None, None
            # selected_invariant = invariants[np.argmax(similarities)]
    else:
        selected_invariant = model.gen(messages, temperature=0, top_k=1)
        selected_invariant = selected_invariant[0].strip()
        selected_invariant = strip_noncode(selected_invariant)
        RichLog.info("Generated invariants")

    return selected_index, selected_invariant

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Generate specs for translation')
    parser.add_argument('-dir',         dest="dir",         required=True,          type=str,   help="Directory to write the generated files")
    parser.add_argument('-overwrite',   dest="overwrite",   action="store_true",                help="Overwrite existing files")
    parser.add_argument('-model',       dest="model",       default="gpt4o",        type=str,   help="Model to use for generation [gpt4o|gpt4|gpt3|gemini|claude]")
    parser.add_argument('-src_lang',    dest="src_lang",    default="c",            type=str,   help="Source language")
    parser.add_argument('-no_sc',       dest="sc",          action="store_false",               help="Don't use self-consistency")
    parser.add_argument('-noinvariant', dest="invariant",   action="store_false",               help="Don't generate invariants")
    parser.add_argument('-notests',     dest="tests",       action="store_false",               help="Don't generate tests")
    parser.add_argument('-nodesc',      dest="desc",        action="store_false",               help="Don't generate descriptions")
    args = parser.parse_args()

    model = get_model_from_name(args.model)

    save_dir        = Path(os.path.dirname(__file__)).joinpath(args.dir)

    if not save_dir.exists():
        save_dir.mkdir()

    success = {"baseline": 0,
               "invariant": 0,
               "test": 0,
               "desc": 0}
    fail = 0
    no_tests = 0

    sc_metadata = pd.DataFrame(columns=["problem_id", "solution_id", "invariant_index", "desc_index", "first_correct_test", "first_incorrect_test", "coverage"])
    sc_metadata = sc_metadata.set_index(['problem_id', 'solution_id'])

    test_dataset = CodeNet(args.src_lang, 'selected')
    cnv = CodeNetVerifier()

    for data in test_dataset.iterator():
        problem_id      = data['filename'].split('/')[-3]
        solution_file   = data['filename'].split('/')[-1]
        sol_id, sol_ext = solution_file.split('.')

        if (not args.overwrite) and (save_dir / problem_id).exists():
            continue

        if not (save_dir / problem_id).exists():
            (save_dir / problem_id).mkdir()

        invariant_save_path = save_dir.joinpath(f"{problem_id}/{sol_id}_invariant.txt")
        desc_save_path = save_dir.joinpath(f"{problem_id}/{sol_id}_desc.txt")
        test_save_path = save_dir.joinpath(f"{problem_id}/{sol_id}_test.txt")

        RichLog.info(f"Processing {problem_id}/{sol_id}")

        try:
            original_code = data['content']
            RichLog.info("Loading provided test cases")
            input_data, ground_truth = CodeNet.get_io(problem_id)

            result = cnv.verify(original_code, args.src_lang, problem_id)
            if result['status'] != "Success":
                print(f"Skipping {data['filename']} because it doesn't solve the problem")
                continue
            
            if not input_data or not ground_truth:
                RichLog.warn("Failed to generate or load test cases. Skipping.")
                no_tests += 1
                continue
            
            if args.invariant:
                RichLog.info("Trying with invariants")
                # Generate invariant (optionally using self-consistency)
                invariant_index, invariant = generate_invariant(original_code, args.src_lang, model, input_data, ground_truth, self_consistency=args.sc, num_candidates=6)
                if invariant is None:
                    RichLog.warn("Failed to generate a self-consistent invariant. Moving on")
                else:
                    invariant_save_path.write_text(invariant)

            if args.tests:
                RichLog.info("Trying with tests")
                test_metadata, (gen_input_data, gen_ground_truth) = generate_tests(original_code, args.src_lang, model, num_tests=10, self_consistency=args.sc)
                if gen_input_data is None or gen_ground_truth is None:
                    RichLog.warn("Failed to generate test cases. Moving on")
                else:
                    test_save_path.write_text(f"Input:\n{gen_input_data}\n\nOutput:\n{gen_ground_truth}")
                
            if args.desc:
                RichLog.info("Trying with descriptions")
                # Generate description (optionally using self-consistency)
                desc_index, desc = generate_desc(original_code, args.src_lang, model, input_data, ground_truth, self_consistency=args.sc, num_candidates=6)
                if desc is None:
                    RichLog.warn("Failed to generate a self-consistent description. Moving on")
                else:
                    desc_save_path.write_text(desc)
            
            if args.sc:
                sc_metadata.loc[(problem_id, sol_id), 'invariant_index'] = invariant_index
                sc_metadata.loc[(problem_id, sol_id), 'desc_index'] = desc_index
                sc_metadata.loc[(problem_id, sol_id), 'first_correct_test'] = test_metadata['first_correct']
                sc_metadata.loc[(problem_id, sol_id), 'first_incorrect_test'] = test_metadata['first_incorrect']
                sc_metadata.loc[(problem_id, sol_id), 'coverage'] = test_metadata['coverage']

                print("Metadata:", invariant_index, desc_index, test_metadata['first_correct'], test_metadata['first_incorrect'], test_metadata['coverage'])

        except ModelException as e:
            print(f"Error: {e}")
            print("Skipping this attempt")
            continue
    
    if args.sc:
        sc_metadata.to_csv(save_dir.joinpath("metadata.csv"), sep="\t", mode='w', index=True)
        RichLog.info(f"Wrote metadata to {save_dir.joinpath('metadata.csv').absolute()}")
    
    # Print success and failure statistics
    RichLog.info("Successes:")
    for key, value in success.items():
        RichLog.info(f"{key}: {value}")
    RichLog.info(f"Failures: {fail}")
    RichLog.info(f"No tests: {no_tests}")
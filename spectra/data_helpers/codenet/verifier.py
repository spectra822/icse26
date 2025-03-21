import os
import json
from pathlib import Path
import tempfile
import subprocess
import threading
import re
import shutil

from typing import Dict

VALGRIND_CODE = 42

class CompileException(Exception):
    pass

class CodeNetVerifier:

    FILE_EXT = {"c": "c",
                "c++": "cpp",
                "rust": "rs",
                "java": "java",
                "python": "py",
                "go": "go",
                "javascript": "js",
                "typescript": "ts"
                }

    def __init__(self):

        self.codenet_dir    = Path(os.environ['CODENET_DIR'])
        self.io_dir         = self.codenet_dir.joinpath('derived', 'input_output', 'data')
        self.temp_dir       = Path(tempfile.mkdtemp(dir=tempfile.gettempdir()))


    def __del__(self):
        # Clean up: remove the temporary file and directory
        shutil.rmtree(self.temp_dir)

    def __compile__(self, input_path, language, output_path, verbose=False, timeout=120):

        cwd = os.getcwd()
        os.chdir(str(self.temp_dir.absolute()))

        if language == 'c':
            cmd = f"gcc --coverage {input_path} -o {output_path}"
        elif language == 'rust':
            cmd = f'RUSTFLAGS="-Awarnings" rustc {input_path} -o {output_path}'
        elif language == 'go':
            cmd = f"go build -o {output_path} {input_path}"
        elif language == "javascript":
            cmd = f"cp {input_path} {output_path}"
        elif language == "typescript":
            cmd = f"npm i --save-dev @types/node; tsc {input_path}; mv {input_path.with_suffix('.js')} {output_path}"
        else:
            os.chdir(cwd)
            raise NotImplementedError(f"Don't know how to compile {language}")

        ERROR_MESSAGE = "Error compiling file:"

        try:
            result = subprocess.run(
                        cmd,
                        shell=True,
                        timeout=timeout,
                        stderr=subprocess.STDOUT if verbose else subprocess.PIPE,
                        stdout=None if verbose else subprocess.PIPE,
                    )
            if result.returncode != 0:
                # For some reason, tsc writes errors to stdout
                compiler_output = result.stdout.decode('utf-8') if language == "typescript" else result.stderr.decode('utf-8')
                raise CompileException(f"{ERROR_MESSAGE}\n{compiler_output}")
            
        except (subprocess.TimeoutExpired, TimeoutError):
            raise CompileException(f"{ERROR_MESSAGE} timeout")
        
        finally:
            os.chdir(cwd)
    

    def __execute__(self, command, sample_input, expected_output, eof=False) -> Dict[str, str]:

        try:
            result = subprocess.run(command, timeout=3, input=sample_input, capture_output=True, encoding="utf-8", errors='replace')
        except (subprocess.TimeoutExpired, TimeoutError):
            return {"status": "Runtime Error",
                    "message": f"Input:\n{sample_input.strip()}\n\nRuntime Error - Timeout",
                    "stdout": "",
                    "stderr": ""}

        if result.returncode != 0:
            if result.returncode == VALGRIND_CODE:
                error_msg = "Valgrind"
            else:
                error_msg = result.stderr
            return {"status": "Runtime Error",
                    "message": f"Input:\n{sample_input.strip()}\n\nRuntime Error - {error_msg}",
                    "stdout": result.stdout,
                    "stderr": result.stderr}
        
        output = result.stdout
        errors = result.stderr

        if expected_output.strip() == output.strip():
            return {"status": "Success", "message": "", "stdout": result.stdout, "stderr": result.stderr}
        else:
            # print("Output doesn't match")
            return {"status": "Incorrect Output",
                    "message": f"Input:\n{sample_input.strip()}\n\nExpected output:\n{expected_output.strip()}\n\nActual output:\n{output.strip()}",
                    "stdout": output.strip(),
                    "stderr": errors.strip()}


    def __execute_manual__(self, out_path, sample_input, expected_output, eof=False) -> Dict[str, str]:

        class Command(object):
            def __init__(self, cmd):
                self.cmd = cmd
                self.process = None

            def run_with_timeout(self, raw_inp, timeout, send_eof=False):
                def target():
                    self.process = subprocess.Popen(self.cmd, shell=False, stdout=subprocess.PIPE, stdin=subprocess.PIPE,
                                                    stderr=subprocess.PIPE, text=True, encoding='utf8', errors='replace')
                    self.process.stdin.write(raw_inp + "\n")
                    self.process.stdin.flush()
                    if send_eof:
                        self.process.stdin.close()
                    self.process.wait()

                timed_out = False
                thread = threading.Thread(target=target)
                thread.start()

                thread.join(timeout)
                if thread.is_alive():
                    self.process.terminate()
                    timed_out = True
                    thread.join()

                return {"returncode":   self.process.returncode,
                        "timed_out":    timed_out,
                        "stdout":       self.process.stdout.read(),
                        "stderr":       self.process.stderr.read()}
        
        command = Command(out_path)
        result = command.run_with_timeout(sample_input, 3, eof)

        if result['timed_out']:
            return {"status": "Runtime Error",
                    "message": f"Input:\n{sample_input.strip()}\n\nRuntime Error - Timeout",
                    "stdout": result['stdout'],
                    "stderr": result['stderr']}

        if result['returncode'] != 0:
            if result['returncode'] == VALGRIND_CODE:
                error_msg = "Valgrind"
            else:
                error_msg = result['stderr']
            return {"status": "Runtime Error",
                    "message": f"Input:\n{sample_input.strip()}\n\nRuntime Error - {error_msg}",
                    "stdout": result['stdout'],
                    "stderr": result['stderr']}

        errors = result['stderr']
        output = result['stdout']

        if expected_output.strip() == output.strip():
            return {"status": "Success", "message": "", "stdout": output.strip(), "stderr": errors.strip()}
        else:
            return {"status": "Incorrect Output",
                    "message": f"Input:\n{sample_input.strip()}\n\nExpected output:\n{expected_output.strip()}\n\nActual output:\n{output.strip()}",
                    "stdout": output.strip(),
                    "stderr": errors.strip()}


    def __cleanup__(self, files_before):
        
        # Clean up any random files that got created during compilation/running
        files_after = list(self.temp_dir.iterdir())
        for file in files_after:
            if file not in files_before:
                if file.is_file():
                    file.unlink()
                else:
                    shutil.rmtree(file)


    def verify(self, solution, language, problem_id) -> Dict[str, str]:

        files_before = list(self.temp_dir.iterdir())

        path_to_temp_source_code = self.temp_dir.joinpath(
            f"code.{self.FILE_EXT[language]}"
        )
        path_to_temp_source_code.write_text(solution)

        out_name    = next(tempfile._get_candidate_names())
        out_path    = self.temp_dir.joinpath(out_name)

        try:
            self.__compile__(path_to_temp_source_code, language, out_path, verbose=False)
        except CompileException as e:
            path_to_temp_source_code.unlink()
            self.__cleanup__(files_before)
            return {"status":  "Compile Error", "message": e, "stdout": "", "stderr": e}

        if not self.io_dir.joinpath(problem_id).exists():
            path_to_temp_source_code.unlink()
            out_path.unlink()
            self.__cleanup__(files_before)
            return {"status": "No tests", "message": "", "stdout": "", "stderr": ""}

        input_data   = self.io_dir.joinpath(problem_id, 'input.txt').read_text()
        ground_truth = self.io_dir.joinpath(problem_id, 'output.txt').read_text()

        if language in ['c', 'rust', 'go']:
            cmd = [out_path]
        elif language in ["javascript", "typescript"]:
            cmd = ['node', out_path]
        else:
            raise NotImplementedError(f"Don't know how to execute {language}")

        result = self.__execute__(cmd, input_data, ground_truth, eof=True)

        out_path.unlink()
        path_to_temp_source_code.unlink()
        self.__cleanup__(files_before)

        return result


    def verify_with_custom_test(self, solution, language, sample_input, expected_output, eof=False, valgrind=True, coverage=True) -> Dict[str, str]:
            
        path_to_temp_source_code = self.temp_dir.joinpath(
            f"code.{self.FILE_EXT[language]}"
        )
        path_to_temp_source_code.write_text(solution)

        out_name    = next(tempfile._get_candidate_names())
        out_path    = self.temp_dir.joinpath(out_name)

        try:
            self.__compile__(path_to_temp_source_code, language, out_path, verbose=False)
        except CompileException as e:
            path_to_temp_source_code.unlink()
            return {"status":  "Compile Error", "message": e, "stdout": "", "stderr": e}

        if language in ['c', 'rust', 'go']:
            command = [out_path]
        elif language in ["javascript", "typescript"]:
            command = ['node', out_path]
        else:
            raise NotImplementedError(f"Don't know how to compile {language}")
        
        if language == "c" and valgrind:
            command = ['valgrind', f'--error-exitcode={VALGRIND_CODE}'] + command
        cwd = os.getcwd()
        os.chdir(str(self.temp_dir.absolute()))
        result = self.__execute__(command, sample_input, expected_output, eof)
        os.chdir(cwd)

        if (result['status'] != "Runtime Error") and coverage and language == "c":
            cwd = os.getcwd()
            os.chdir(str(self.temp_dir.absolute()))
            coverage_res = subprocess.run(['gcov', path_to_temp_source_code], shell=False, timeout=3, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
            os.chdir(cwd)

            if coverage_res.returncode != 0:
                result['stderr']    += f"\nError running gcov: {coverage_res.stderr.decode('utf-8')}"
                result['coverage']  = -1
            else:
                raw_output = coverage_res.stdout.decode('utf-8')
                if "No executable lines" in raw_output:
                    result['coverage'] = 0
                else:
                    pattern = r'Lines executed:(\d+\.\d+)%'
                    match = re.search(pattern, raw_output)
                    if match:
                        percentage = match.group(1)
                        result['coverage'] = float(percentage) / 100
                    else:
                        result['coverage'] = -1
                    # coverage = pd.read_csv(path_to_temp_source_code.with_suffix('.c.gcov'), sep=':', header=None)
                    # line_counts = pd.to_numeric(coverage[0], errors='coerce').dropna()
                    # result['coverage'] = len(line_counts[line_counts > 0]) / float(len(line_counts))
                    if path_to_temp_source_code.with_suffix('.c.gcov').is_file():
                        path_to_temp_source_code.with_suffix('.c.gcov').unlink()

        if coverage and language != "c":
            print("Warning - coverage is only supported for C language")
            result['coverage'] = -1
        
        if path_to_temp_source_code.with_suffix('.gcno').is_file():
            path_to_temp_source_code.with_suffix('.gcno').unlink()
        if path_to_temp_source_code.with_suffix('.gcda').is_file():
            path_to_temp_source_code.with_suffix('.gcda').unlink()
        
        out_path.unlink()
        path_to_temp_source_code.unlink()

        return result
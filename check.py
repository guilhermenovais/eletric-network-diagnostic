import os
import subprocess
from difflib import ndiff
from termcolor import colored


class bcolors:
    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


def run_test_cases(executable, testcases_dir):
    input_dir = os.path.join(testcases_dir, "inputs")
    output_dir = os.path.join(testcases_dir, "outputs")

    for i in range(1, 9):
        input_file = os.path.join(input_dir, f"testCase{i:02}.txt")
        expected_output_file = os.path.join(output_dir, f"testCase{i:02}.txt")

        if not os.path.exists(input_file) or not os.path.exists(expected_output_file):
            print(f"Input or output file for testCase{i:02} is missing.")
            continue

        # Run the executable
        try:
            result = subprocess.run(
                [executable],
                input=open(input_file, "r").read(),
                text=True,
                capture_output=True,
                check=True,
            )
        except subprocess.CalledProcessError as e:
            print(f"Error running testCase{i:02}: {e}")
            continue

        # Get the expected and actual output
        actual_output = result.stdout.splitlines()
        with open(expected_output_file, "r") as f:
            expected_output = f.read().splitlines()

        # Compare outputs
        if actual_output != expected_output:
            print(f"Test case testCase{i:02} failed:")
            print("Actual Output:")
            diff = ndiff(expected_output, actual_output)
            print("\n".join(diff), end="\n")


if __name__ == "__main__":
    executable_path = "./tp2"
    testcases_path = "./testcases"

    if not os.path.exists(executable_path):
        print("Executable not found.")
    elif not os.path.exists(testcases_path):
        print("Test cases directory not found.")
    else:
        run_test_cases(executable_path, testcases_path)

import argparse
import os
import subprocess

parser = argparse.ArgumentParser(description = 'Runs test cases for assignment')
parser.add_argument(metavar="assignment diretory", dest="dir", help="Directory that contains the test cases")
parser.add_argument("-c", "--code", dest="code_file", default="main.py")
parser.add_argument("-p", "--print_output", action="store_true")
parser.add_argument("-f", "--float-tolerance", default=0, type=float)

args = parser.parse_args()

def main(dir: str, code_file: str, print_output: bool = False, float_tolerance: float = 0) -> None:
    dir = os.path.join(os.path.dirname(__file__), dir)
    in_dir = os.path.join(dir, "in")
    out_dir = os.path.join(dir, "out")

    executable = os.path.join(dir, code_file)

    for in_file in sorted(os.listdir(in_dir), key = lambda x: int(x[4:-3])):
        filename = in_file[:in_file.rindex('.')]

        in_path = os.path.join(in_dir, in_file)
        out_path = os.path.join(out_dir, filename + ".out")

        result = subprocess.run(["python", executable],
                                stdin = open(in_path),
                                capture_output = True,
                                cwd = dir)
        output = result.stdout.decode('utf-8').rstrip('\n\r') + '\n'
        errors = result.stderr.decode('utf-8')

        expected = ""
        with open(out_path) as file:
            expected = file.read().rstrip('\n\r')+"\n"

        passed = True
        if(float_tolerance):
            out_number = float(output)
            exp_number = float(expected)
            passed = (abs(out_number - exp_number) <= float_tolerance)
        else:
            passed = (output == expected)

        text_color = '\033[0m'
        if passed:
            text_color = '\033[92m'
        else:
            text_color = '\033[91m'

        print(text_color + filename + '\033[0m')
        if(print_output):
            if(errors):
                print(errors)
            else:
                print("=====output=====")
                print(output, end="")
                print("=====expect=====")
                print(expected)

if __name__ == "__main__":
    main(**vars(args))
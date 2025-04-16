import subprocess
import logging_config

logger = logging_config.logger


def compile_cpp_code(debug=True):
    logger.info("compiling main.cpp")

    flags_debug = ["-Wall", "-Wextra", "-Wpedantic", "-Werror"]
    flags_release = ["-O3", "-march=native", "-ffast-math", "-funsafe-math-optimizations", "-fno-math-errno", "-fno-trapping-math"]

    cpp_file = "main.cpp"
    output_file = "main"

    compile_command = ["g++", cpp_file, "-o", output_file]
    if debug:
        compile_command.extend(flags_debug)
    else:
        compile_command.extend(flags_release)
    subprocess.run(compile_command, check=True)


def run_and_parse():
    logger.info("running main.exe")
    output_file = "main.exe"

    result = subprocess.run([f"./{output_file}"], capture_output=True, text=True, check=True)
    output = result.stdout.strip()
    print(output)

    return output


def main():
    compile_cpp_code(debug=False)
    run_and_parse()


if __name__ == "__main__":
    main()

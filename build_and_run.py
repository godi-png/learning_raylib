#!/usr/bin/env python3
import os
import sys
import subprocess
import platform

PROJECT_NAME = "learning_main"
BUILD_DIR = "build"

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = SCRIPT_DIR

OS_SYSTEM = platform.system()
if OS_SYSTEM == "Windows":
    try:
        subprocess.run(
            ["clear"], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        CLEAR_CMD = "clear"
    except (subprocess.CalledProcessError, FileNotFoundError):
        CLEAR_CMD = "cls"
    EXECUTABLE_EXT = ".exe"
else:
    CLEAR_CMD = "clear"
    EXECUTABLE_EXT = ""

BUILD_CONFIG = "Debug"
DEBUG = True
if len(sys.argv) > 1:
    BUILD_CONFIG = sys.argv[1]


# helper function
def run_command(command, cwd=None, check=True):
    """
    Run shell commands with stdout
    Args:
        command (list or str): The command and its arguments as a list, or a string.
        cwd (str, optional): The current working directory for the command.
        check (bool): If True, raise an exception if the command returns a non-zero exit code.
    """
    print(f"Executing: {' '.join(command) if isinstance(command, list) else command}")
    try:
        # Use shell=True for simple commands like 'clear'/'cls'
        # For actual build/run commands, prefer shell=False for better security and explicit control
        if isinstance(command, str) and (command == "clear" or command == "cls"):
            subprocess.run(command, shell=True, check=check)
        else:
            subprocess.run(command, cwd=cwd, check=check)
    except subprocess.CalledProcessError as e:
        print(f"Error: Command failed with exit code {e.returncode}")
        print(f"Command: {e.cmd}")
        if e.stderr:
            print(f"Stderr: {e.stderr.decode()}")
        if e.stdout:
            print(f"Stdout: {e.stdout.decode()}")
        sys.exit(1)
    except FileNotFoundError:
        print(
            f"Error: Command '{command[0] if isinstance(command, list) else command.split()[0]}' not found."
        )
        print(
            "Please ensure CMake and your compiler (g++/Visual Studio) are installed and in your system's PATH."
        )
        sys.exit(1)


# Build

run_command([CLEAR_CMD])

print(f"--- Starting Build Process for '{PROJECT_NAME}' ({BUILD_CONFIG}) ---")

# Configure CMake
# -S <source_dir>: Specifies the path to the source directory (where CMakeLists.txt is)
# -B <build_dir>: Specifies the path to the build directory (where build files will be generated)
build_path = os.path.join(PROJECT_ROOT, BUILD_DIR)
print(f"Configuring CMake in '{build_path}'...")
run_command(["cmake", "-S", PROJECT_ROOT, "-B", build_path])

# Build
# --build <build_dir>: Builds a CMake-generated project binary tree
# --config <config>: Specifies the build configuration (e.g., Debug, Release)
print("Building project...")
run_command(["cmake", "--build", build_path, "--config", BUILD_CONFIG])

print("Build complete.")

# Run Process

print("--- Running Executable ---")

if DEBUG:
    executable_path = os.path.join(
        build_path, "bin", BUILD_CONFIG, PROJECT_NAME + EXECUTABLE_EXT
    )
else:
    executable_path = os.path.join(build_path, "bin", PROJECT_NAME + EXECUTABLE_EXT)

if executable_path:
    print(f"Executing: {executable_path}")
    # On Linux/macOS, ensure the executable has execute permissions
    if OS_SYSTEM != "Windows":
        os.chmod(executable_path, 0o755)  # rwxr-xr-x

    # For Windows, use os.startfile to run without blocking the script,
    # similar to 'START ""' in batch. For Linux/macOS, just run directly.
    if OS_SYSTEM == "Windows":
        os.startfile(executable_path)
    else:
        run_command([executable_path])
else:
    print(
        f"Error: Executable '{PROJECT_NAME}{EXECUTABLE_EXT}' not found at expected paths."
    )
    print(
        "Please ensure the project builds successfully and check your CMakeLists.txt for output path settings."
    )
    print("Tried paths:")

    print(f"  - {executable_path}")
    sys.exit(1)

run_command([CLEAR_CMD])

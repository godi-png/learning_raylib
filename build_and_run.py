#!/bin/env python3
import os
import sys
import subprocess
import platform

# --- Configuration ---
PROJECT_NAME = "learning_main"
BUILD_DIR = "build"

# Absolute path of script location
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = SCRIPT_DIR

# Determine OS for clear command and executable extension
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
else:  # Linux, macOS, etc.
    CLEAR_CMD = "clear"
    EXECUTABLE_EXT = ""

# Determine the build configuration (e.g., Debug, Release)
# Default to 'Debug' if no argument is provided
BUILD_CONFIG = "Debug"
if len(sys.argv) > 1:
    BUILD_CONFIG = sys.argv[1]


# --- Helper Function for Running Commands ---
def run_command(command, cwd=None, check=True, run_in_background=False):
    """
    Runs a shell command and prints its output.
    Args:
        command (list or str): The command and its arguments as a list, or a string.
        cwd (str, optional): The current working directory for the command.
        check (bool): If True, raise an exception if the command returns a non-zero exit code.
        run_in_background (bool): If True, run the command in the background (primarily for Windows).
    """
    print(f"Executing: {' '.join(command) if isinstance(command, list) else command}")
    try:
        if isinstance(command, str) and (command == "clear" or command == "cls"):
            subprocess.run(command, shell=True, check=check)
        elif OS_SYSTEM == "Windows" and run_in_background:
            # For Windows, use Popen to run in background and set CWD
            subprocess.Popen(command, cwd=cwd)
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


# --- Build Process ---

run_command([CLEAR_CMD])

print(f"--- Starting Build Process for '{PROJECT_NAME}' ({BUILD_CONFIG}) ---")

# Configure CMake
# -S <source_dir>: Specifies the path to the source directory (where CMakeLists.txt is)
# -B <build_dir>: Specifies the path to the build directory (where build files will be generated)
# The build_path should always be PROJECT_ROOT/BUILD_DIR for the -B argument
build_path = os.path.join(PROJECT_ROOT, BUILD_DIR)
print(f"Configuring CMake in '{build_path}'...")
run_command(["cmake", "-S", PROJECT_ROOT, "-B", build_path])

# Build
# --build <build_dir>: Builds a CMake-generated project binary tree
# --config <config>: Specifies the build configuration (e.g., Debug, Release)
print("Building project...")
run_command(["cmake", "--build", build_path, "--config", BUILD_CONFIG])

print("Build complete.")

# --- Run Process ---

print("--- Running Executable ---")

# Determine the executable path based on common CMake output conventions
# These paths cover single-config generators (like Makefiles) and multi-config (like Visual Studio)
executable_paths_to_try = [
    os.path.join(build_path, "bin", PROJECT_NAME + EXECUTABLE_EXT),
    os.path.join(build_path, BUILD_CONFIG, "bin", PROJECT_NAME + EXECUTABLE_EXT),
    os.path.join(
        build_path, PROJECT_NAME + EXECUTABLE_EXT
    ),  # Fallback for non-bin output
    os.path.join(
        build_path, BUILD_CONFIG, PROJECT_NAME + EXECUTABLE_EXT
    ),  # Fallback for multi-config, non-bin output
]

found_executable_path = None
for path in executable_paths_to_try:
    if os.path.exists(path):
        found_executable_path = path
        break

if found_executable_path:
    print(f"Executing: {found_executable_path}")
    # On Linux/macOS, ensure the executable has execute permissions
    if OS_SYSTEM != "Windows":
        os.chmod(found_executable_path, 0o755)  # rwxr-xr-x

    # Run the executable with the project root as its current working directory (cwd)
    # For Windows, we want it to run in the background (like START "" in .bat)
    run_command(
        [found_executable_path],
        cwd=PROJECT_ROOT,
        run_in_background=(OS_SYSTEM == "Windows"),
    )
else:
    print(
        f"Error: Executable '{PROJECT_NAME}{EXECUTABLE_EXT}' not found at expected paths."
    )
    print(
        "Please ensure the project builds successfully and check your CMakeLists.txt for output path settings."
    )
    print("Tried paths:")
    for path in executable_paths_to_try:
        print(f"  - {path}")
    sys.exit(1)

run_command([CLEAR_CMD])

#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

source "$SCRIPT_DIR/AlertSymbols.sh"
set -e  # Exit on any failure

# Go to project root
cd "$(dirname "$0")/.."

# -----------------------------
# Python and Pillow Setup
# Why: we have a tool, ./scripts/gif_to_spritesheet.py, 
#      depends on python and pillow to run
# -----------------------------
if command -v python3 &> /dev/null \
    && python3 --version &> /dev/null; then
    PYTHON_CMD=python3
elif command -v python &> /dev/null \
    && python --version &> /dev/null; then
    PYTHON_CMD=python
else
    echo -e "${CROSS}Python3 was not found"
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "${INFO}installing python 3 via apt..."
        sudo apt update && sudo apt install -y python3 python3-pip
        PYTHON_CMD=python3
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo -e "${INFO}installing python3 via Homebrew..."
        brew install python3
        PYTHON_CMD=python3 
    else
        echo -e "${CROSS}Unsupported OS, probably Windows. Need to install manually before this script will continue."
        exit 1;
    fi
fi

if ! $PYTHON_CMD -m pip show pillow &> /dev/null; then
    echo -e "${INFO}Installing Pillow"
    echo -e "Python CMD: ${PYTHON_CMD}"
    $PYTHON_CMD -m pip install --user pillow
else
    echo -e "${CHECK}Pillow is installed"
fi

# -----------------------------
# Check for Ninja
# -----------------------------
if command -v ninja >/dev/null 2>&1; then
    GENERATOR="Ninja"
else
    echo -e "${INFO}Ninja not found. Falling back to Visual Studio 17 2022 generator."
    GENERATOR="Visual Studio 17 2022"
fi

# -----------------------------
# Ensure GLFW exists
# -----------------------------
if [ ! -d "libs/glfw" ]; then
    echo "Cloning GLFW..."
    git clone https://github.com/glfw/glfw.git libs/glfw
fi


# -----------------------------
# Create build directory
# -----------------------------
mkdir -p build
cd build

# -----------------------------
# Run CMake configuration
# -----------------------------
if [ ! -f "CMakeCache.txt" ]; then
    echo "Configuring CMake..."
    cmake .. -G "$GENERATOR" -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
else
    echo "Using existing CMake cache..."
fi

# -----------------------------
# Build project
# -----------------------------
echo "Building project..."
cmake --build . --config Release

# -----------------------------
# Run executable
# -----------------------------
echo -e "${CHECK}Running Game..."
if [ -f "Release/GameEngineFun.exe" ]; then
    ./Release/GameEngineFun.exe
else
    echo "Executable not found!"
fi


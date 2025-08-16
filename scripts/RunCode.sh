#!/bin/bash
set -e  # Exit on any failure

# Go to project root
cd "$(dirname "$0")/.."

# -----------------------------
# Step 0: Check for Ninja
# -----------------------------
if command -v ninja >/dev/null 2>&1; then
    GENERATOR="Ninja"
else
    echo "Ninja not found. Falling back to Visual Studio 17 2022 generator."
    GENERATOR="Visual Studio 17 2022"
fi

# -----------------------------
# Step 1: Ensure GLFW exists
# -----------------------------
if [ ! -d "libs/glfw" ]; then
    echo "Cloning GLFW..."
    git clone https://github.com/glfw/glfw.git libs/glfw
fi


# -----------------------------
# Step 2: Create build directory
# -----------------------------
mkdir -p build
cd build

# -----------------------------
# Step 3: Run CMake configuration
# -----------------------------
if [ ! -f "CMakeCache.txt" ]; then
    echo "Configuring CMake..."
    cmake .. -G "$GENERATOR" -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
else
    echo "Using existing CMake cache..."
fi

# -----------------------------
# Step 4: Build project
# -----------------------------
echo "Building project..."
cmake --build . --config Release

# -----------------------------
# Step 5: Run executable
# -----------------------------
echo "Running program..."
if [ -f "Release/GameEngineFun.exe" ]; then
    ./Release/GameEngineFun.exe
else
    echo "Executable not found!"
fi


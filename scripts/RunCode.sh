#!/bin/bash
set -e  # Exit if any command fails

# Go to project root (one level up from this script's folder)
cd "$(dirname "$0")/.."

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake only if no cache exists
if [ ! -f CMakeCache.txt ]; then
    echo "Running CMake configuration..."
    cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
fi

# Build the project
echo "Building project..."
cmake --build . --config Release

# Run the executable (adjust name if different)
echo "Running program..."
../build/Release/GameEngineFun.exe


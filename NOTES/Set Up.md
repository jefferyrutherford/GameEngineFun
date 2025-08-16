# GameEngineFun Setup Checklist

This guide helps you get the project running locally, including dependencies like GLFW and GLAD.

---

## 1. Clone the Repository

```bash
git clone https://github.com/yourusername/GameEngineFun.git
cd GameEngineFun
```
## 2. Install Dependencies
## Required Tools
- CMake (≥ 3.20 recommended)
- Visual Studio Build Tools (with C++ workload) or w64devkit
- Python 3 (for GLAD generation)
- pip packages: jinja2

```bash
python -m pip install --upgrade pip
pip install jinja2
```
- Ninja (optional, for faster builds):

```bash
choco install ninja
#or add to PATH if already installed
```
## 3. Prepare Libraries
## GLFW
```bash
# If not already in libs/glfw
git clone https://github.com/glfw/glfw.git libs/glfw
```
## GLAD
- Manual installation required (currently no working automated download).
- Make sure libs/glad contains:
```

libs/glad/
├─ include/
│  └─ glad/glad.h
└─ src/
   └─ glad.c
```
- See GLAD_INSTALL.md for detailed instructions.
## 4. Build the Project
```bash
# Create build directory
mkdir -p build
cd build

# Configure CMake
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build project
cmake --build . --config Release
```
## 5. Run the Executable
```bash
./Release/GameEngineFun.exe
```
## 6. Notes
- compile_commands.json will be generated if you use -DCMAKE_EXPORT_COMPILE_COMMANDS=ON.
	- needed for lsp to work properly or something. 
- Keep the NOTES/ folder in Git to track project documentation.
- If any library updates are required (GLAD/GLFW), check RunCode.sh.

## 7. Optional: RunCode.sh
Automates cloning, building, and running (make sure GLAD is manually installed first).

```bash
./scripts/RunCode.sh
```
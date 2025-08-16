cmake_minimum_required(VERSION 3.15)
project(GameEngineFun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Include project headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glad/include)

# Add GLFW subdirectory
add_subdirectory(libs/glfw)

# Add executable
add_executable(GameEngineFun
    main.cpp
    Player.cpp
    libs/glad/src/glad.c
)

# Link libraries
target_link_libraries(GameEngineFun PRIVATE glfw)
target_link_libraries(GameEngineFun PRIVATE opengl32)


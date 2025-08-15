cmake_minimum_required(VERSION 3.15)
project(GameEngineFun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Tell CMake to find GLFW installed by vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

#include the include directory, my life is complete
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(GameEngineFun 
    main.cpp
    Player.cpp
)

target_link_libraries(GameEngineFun PRIVATE glfw)
target_link_libraries(GameEngineFun PRIVATE opengl32)
target_link_libraries(GameEngineFun PRIVATE glad::glad)


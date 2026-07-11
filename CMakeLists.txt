cmake_minimum_required(VERSION 3.16)

project(Vortex)

# Set build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Set build artifacts directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(${Vortex}
    Main.cpp
    Engine/Client/cl_main.cpp
    Engine/Server/sv_main.cpp
)
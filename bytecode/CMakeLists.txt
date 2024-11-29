# bytecode/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Create a static library for bytecode
add_library(bytecode STATIC
    src/bytecode.cpp
)

# Specify include directories for bytecode including instruction.h
target_include_directories(bytecode PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
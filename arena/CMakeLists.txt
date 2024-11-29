# arena/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Create an interface library for arena
add_library(arena INTERFACE)

# Specify include directories for arena, allowing it to include instruction.h
target_include_directories(arena INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/bytecode/include>  # Dependency on instruction.h
)
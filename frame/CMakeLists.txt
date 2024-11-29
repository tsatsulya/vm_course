# frame/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Create a static library for frame
add_library(frame STATIC
    src/frame.cpp
)

# Specify include directories for frame
target_include_directories(frame PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/bytecode/include>  # For instruction.h
)

# Link dependencies if any (none mentioned directly here)
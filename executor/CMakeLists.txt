# executor/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Create a static library for executor
add_library(executor STATIC
    src/executor.cpp
)

# Specify include directories for executor
target_include_directories(executor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/bytecode/include>  # For instruction.h
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/frame/include>     # For method.h
)

# Link dependencies: executor requires arena and bytecode
target_link_libraries(executor PUBLIC arena bytecode frame)
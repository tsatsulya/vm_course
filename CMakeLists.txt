# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(VM)

set(CMAKE_CXX_STANDARD 20) # or 17, 20 etc.
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for the components
add_subdirectory(arena)
add_subdirectory(bytecode)
add_subdirectory(executor)
add_subdirectory(frame)
add_subdirectory(benchmarks)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(main PUBLIC executor)


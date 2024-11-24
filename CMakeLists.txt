cmake_minimum_required(VERSION 3.28)

project(vm LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS        OFF)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(executor)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(main PUBLIC executor)

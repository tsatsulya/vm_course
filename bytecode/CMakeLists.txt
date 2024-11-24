cmake_minimum_required(VERSION 3.10)

project(Bytecode)

set(SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/bytecode.cpp)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(bytecode STATIC src/bytecode.cpp)
target_include_directories(bytecode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
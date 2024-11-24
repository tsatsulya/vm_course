cmake_minimum_required(VERSION 3.10)

set(SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/frame.cpp)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

project(Frame)

add_subdirectory(../bytecode ${CMAKE_CURRENT_BINARY_DIR}/bytecode_build)

add_library(frame STATIC ${SOURCE})
target_include_directories(frame PUBLIC ${PROJECT_INCLUDE_DIR})

target_link_libraries(frame PUBLIC bytecode)
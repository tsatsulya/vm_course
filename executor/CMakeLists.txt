cmake_minimum_required(VERSION 3.10)

set(SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/executor.cpp)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

project(Executor)

# add_subdirectory(../bytecode ${CMAKE_CURRENT_BINARY_DIR}/bytecode_build)
add_subdirectory(../frame ${CMAKE_CURRENT_BINARY_DIR}/frame_build)
add_library(executor STATIC ${SOURCE})
target_include_directories(executor PUBLIC ${PROJECT_INCLUDE_DIR})

target_link_libraries(executor PUBLIC frame)
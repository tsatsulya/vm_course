cmake_minimum_required(VERSION 3.10)
project(Benchrunner)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20) # or 17, 20 etc.
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB BENCHMARKS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(benchmark_file ${BENCHMARKS})
    get_filename_component(benchmark_name ${benchmark_file} NAME_WE)

    add_executable(${benchmark_name} ${benchmark_file})
    target_include_directories(${benchmark_name} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/executor/inclulde>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/frame/inclulde>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/instruction/inclulde>
    )
    target_link_libraries(${benchmark_name} executor frame)
endforeach()

add_custom_target(run_all_benchmarks ALL DEPENDS ${BENCHMARKS})

# You can also add individual run commands if needed
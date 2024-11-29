cmake_minimum_required(VERSION 3.27)

project(VIRTUAL_MACHINE LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_library(vm_lib STATIC
    ${SOURCE_DIR}/builder.cpp
    ${SOURCE_DIR}/executor.cpp
    ${SOURCE_DIR}/machine.cpp
)
target_include_directories(vm_lib PUBLIC ${INCLUDE_DIR})

set(TARGET_NAME vm)
add_executable(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE vm_lib)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${TARGET_NAME})

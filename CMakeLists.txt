cmake_minimum_required(VERSION 4.00)
project(cpp-core)

# ------------------------------------------------------------------------------
# Global C++ configuration
# ------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Header-only algebra library (INTERFACE target)
# ------------------------------------------------------------------------------

add_library(fs_math_algebra INTERFACE)

target_include_directories(fs_math_algebra INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_compile_features(fs_math_algebra INTERFACE cxx_std_20)

# ------------------------------------------------------------------------------
# Compiler warnings (library consumers inherit these)
# ------------------------------------------------------------------------------

if (MSVC)
    target_compile_options(fs_math_algebra INTERFACE
            /W4
            /permissive-
            /we4265   # non-virtual dtor with virtuals
            /we5204   # virtual dtor rule
            /wd4100   # unused parameter
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(fs_math_algebra INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wnon-virtual-dtor
            -Wreorder
            -Wmaybe-uninitialized
            -Wunused-variable
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(fs_math_algebra INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wnon-virtual-dtor
            -Wreorder
            -Wsometimes-uninitialized
            -Wunused-variable
    )
endif()

# ------------------------------------------------------------------------------
# Example / test executable
# ------------------------------------------------------------------------------

# setting header files
set(HEADER_FILES
        src/Array.h
        src/BinaryTree.h
        src/Deque.h
        src/DoubleList.h
        src/Queue.h
        src/SearchTree.h
        src/SingleList.h
        src/Stack.h
        src/Vector.h
)

# setting source files
set(SOURCE_FILES
        main.cpp
)

# adding main executable
add_executable(cpp-core
        main.cpp
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

# ------------------------------------------------------------------------------
# Platform-specific configuration
# ------------------------------------------------------------------------------

if (APPLE)
    target_compile_options(fs_math_example PRIVATE
            -Wno-deprecated-declarations
    )

    find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
    find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)
    find_library(COREVIDEO_FRAMEWORK CoreVideo REQUIRED)

    target_link_libraries(fs_math_example PRIVATE
            ${COCOA_FRAMEWORK}
            ${IOKIT_FRAMEWORK}
            ${COREFOUNDATION_FRAMEWORK}
            ${COREVIDEO_FRAMEWORK}
    )
endif()

# ------------------------------------------------------------------------------
# Status output
# ------------------------------------------------------------------------------

message(STATUS "Compiler:     ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build type:   ${CMAKE_BUILD_TYPE}")
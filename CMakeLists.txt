cmake_minimum_required(VERSION 3.25)
project(structura
        VERSION 0.1.0
        DESCRIPTION "Modern C++ library for data structures, algorithms, mathematical types and operations"
        LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(STRUCTURA_BUILD_EXAMPLES "Build structura examples" ON)
option(STRUCTURA_BUILD_TESTS "Build structura tests" ON)

add_library(structura INTERFACE)
add_library(structura::structura ALIAS structura)

target_compile_features(structura INTERFACE cxx_std_20)

target_include_directories(structura
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE
        ${PROJECT_SOURCE_DIR}/external/doctest
)

if (MSVC)
    target_compile_options(structura INTERFACE
            /W4
            /permissive-
            /we4265
            /we5204
            /wd4100
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(structura INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wnon-virtual-dtor
            -Wreorder
            -Wmaybe-uninitialized
            -Wunused-variable
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(structura INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wnon-virtual-dtor
            -Wreorder
            -Wsometimes-uninitialized
            -Wunused-variable
    )
endif()

if (STRUCTURA_BUILD_EXAMPLES)
    add_executable(structura-example examples/main.cpp)
    target_link_libraries(structura-example PRIVATE structura::structura)
endif()

if (STRUCTURA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS structura
        EXPORT structuraTargets
)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT structuraTargets
        FILE structuraTargets.cmake
        NAMESPACE structura::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/structura
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/structuraConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/structuraConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/structura
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/structuraConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/structuraConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/structuraConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/structura
)
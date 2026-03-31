cmake_minimum_required(VERSION 3.25)
project(structura-tests)

add_executable(structura-tests
        test_main.cpp
        core/array_tests.cpp
        core/binary_tree_tests.cpp
        core/deque_tests.cpp
        core/double_list_tests.cpp
        core/queue_tests.cpp
        core/search_tree_tests.cpp
        core/single_list_tests.cpp
        core/stack_tests.cpp
        core/vector_tests.cpp
)

target_link_libraries(structura-tests PRIVATE
        structura::structura
        doctest
)

add_test(NAME structura-tests COMMAND structura-tests)
cmake_minimum_required(VERSION 3.9.3)

add_executable(solver_tests solver_tests.cpp)
target_link_libraries(solver_tests gtest_main)
add_test(test NAME solver_testing COMMAND solver_tests)
add_custom_command(
    TARGET solver_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/top95
            ${CMAKE_CURRENT_BINARY_DIR}/top95)

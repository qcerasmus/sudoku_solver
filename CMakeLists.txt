cmake_minimum_required(VERSION 3.10)

project (sudoku_solver)

include_directories(include)

add_executable(sudoku_solver main.cpp)

set_property(TARGET sudoku_solver PROPERTY CXX_STANDARD 17)

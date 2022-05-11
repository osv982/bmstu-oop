cmake_minimum_required(VERSION 3.7.0)

project(lab-02 LANGUAGES CXX)

add_library(matrix
    src/except.cpp
)

target_include_directories(matrix
    PUBLIC include)

add_executable(runner
    test/runner.cpp
    test/matrix.cpp
    test/vector.cpp
)

target_link_libraries(runner
    matrix)

target_link_libraries(runner
    CppUTest)
cmake_minimum_required(VERSION 3.10)
project(vector)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_executable(test_vector.exe test_vector.cpp Vector.h)


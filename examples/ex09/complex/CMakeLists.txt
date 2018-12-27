cmake_minimum_required(VERSION 3.10)
project(complex)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Complex.h Complex.cpp)

add_executable(test_complex.exe test_complex.cpp ${SOURCES})


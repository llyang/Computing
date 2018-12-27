cmake_minimum_required(VERSION 3.10)
project(rational)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Rational.h Rational.cpp)

add_executable(test_rational.exe test_rational.cpp ${SOURCES})


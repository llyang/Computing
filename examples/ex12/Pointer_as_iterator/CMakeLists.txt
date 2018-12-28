cmake_minimum_required(VERSION 3.10)
project(pointer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Vector.h Vector.cpp List.h List.cpp)

add_executable(test_pointer.exe test_pointer.cpp ${SOURCES})


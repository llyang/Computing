cmake_minimum_required(VERSION 3.10)
project(list)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES List.h List.cpp)

add_executable(test_list.exe test_list.cpp ${SOURCES})


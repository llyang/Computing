cmake_minimum_required(VERSION 3.10)
project(chrono)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Chrono.h Chrono.cpp)

add_executable(test_date.exe test_date.cpp ${SOURCES})


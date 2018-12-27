cmake_minimum_required(VERSION 3.10)
set(MAIN calc-2.0)
project(${MAIN})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_executable(${MAIN}.exe ${MAIN}.cpp)

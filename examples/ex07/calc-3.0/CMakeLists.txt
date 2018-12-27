cmake_minimum_required(VERSION 3.10)
set(MAIN calc-3.0)
project(${MAIN})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Token.h Token_stream.h Token_stream.cpp Calculator.h Calculator.cpp
  Variable.h Variable.cpp)

add_executable(${MAIN}.exe ${MAIN}.cpp ${SOURCES})


cmake_minimum_required(VERSION 3.10)
project(calc-3.x)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Token.h Token_stream.h Token_stream.cpp Calculator.h Calculator.cpp
  Variable.h Variable.cpp)

foreach(ex calc-3.0 calc-3.1 calc-3.2 calc-3.3)
  add_executable(${ex}.exe ${ex}.cpp ${SOURCES})
endforeach(ex)


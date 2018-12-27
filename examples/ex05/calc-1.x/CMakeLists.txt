cmake_minimum_required(VERSION 3.10)
project(calc-1.x)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

foreach(ex calc-1.0 calc-1.1)
  add_executable(${ex}.exe ${ex}.cpp)
endforeach(ex)



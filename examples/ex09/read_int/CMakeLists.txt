cmake_minimum_required(VERSION 3.10)
project(read_int)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

foreach(ex read_int read_int_new)
  add_executable(${ex}.exe ${ex}.cpp)
endforeach(ex)



cmake_minimum_required(VERSION 3.10)
project(misc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

foreach(ex test_char test_map)
  add_executable(${ex}.exe ${ex}.cpp)
endforeach(ex)



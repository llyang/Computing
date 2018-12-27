cmake_minimum_required(VERSION 3.10)
project(ex02)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

foreach(ex ex02a ex02b ex02c ex02d ex02e ex02f ex02g ex02h ex02i ex02j ex02k)
  add_executable(${ex}.exe ${ex}.cpp)
endforeach(ex)



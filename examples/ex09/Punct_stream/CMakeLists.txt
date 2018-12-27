cmake_minimum_required(VERSION 3.10)
project(Punct_stream)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Punct_stream.h Punct_stream.cpp)

foreach(ex test_csv test_ps)
  add_executable(${ex}.exe ${ex}.cpp ${SOURCES})
endforeach(ex)


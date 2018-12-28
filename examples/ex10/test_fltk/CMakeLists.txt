cmake_minimum_required(VERSION 3.10)
project(test_fltk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
link_directories(${FLTK_LIBRARY_DIR})

add_executable(test_fltk.exe test_fltk.cpp)
target_link_libraries(test_fltk.exe ${FLTK_LIBRARIES})


cmake_minimum_required(VERSION 3.10)
project(Animal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(SOURCES Animal.h Animal.cpp)

add_executable(test.exe test.cpp ${SOURCES})


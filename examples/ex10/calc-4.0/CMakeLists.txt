cmake_minimum_required(VERSION 3.11)
project(calc-4.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
link_directories(${FLTK_LIBRARY_DIR})

find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

add_subdirectory(Graph_lib)

set(SOURCES calc-4.0.cpp Calculator.h Calculator.cpp
  Token.h Token_stream.h Token_stream.cpp Variable.h Variable.cpp)

add_executable(calc-4.0.exe ${SOURCES} ${GRAPH_LIB})
target_link_libraries(calc-4.0.exe ${FLTK_LIBRARIES}
  ${JPEG_LIBRARIES} ${PNG_LIBRARIES})


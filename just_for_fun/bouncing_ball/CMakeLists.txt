cmake_minimum_required(VERSION 3.10)
project(bouncing_ball)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
link_directories(${FLTK_LIBRARY_DIR})

find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

add_subdirectory(Graph_lib)

set(SOURCES bouncing_ball.cpp constants.h
  My_window.cpp My_window.h Scene.cpp Scene.h
  Ball.cpp Ball.h Paddle.cpp Paddle.h Block.cpp Block.h)

add_executable(bouncing_ball.exe ${SOURCES} ${GRAPH_LIB})
target_link_libraries(bouncing_ball.exe ${FLTK_LIBRARIES}
  ${JPEG_LIBRARIES} ${PNG_LIBRARIES})

file(COPY blue.jpg DESTINATION ${CMAKE_BINARY_DIR})

cmake_minimum_required(VERSION 3.10)
project(test_graph_lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
link_directories(${FLTK_LIBRARY_DIR})

find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

add_subdirectory(Graph_lib)

foreach(ex test test_animation test_automove test_keyboard test_move test_thread test_vector_ref)
  add_executable(${ex}.exe ${ex}.cpp ${GRAPH_LIB})
  target_link_libraries(${ex}.exe ${FLTK_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES})
endforeach(ex)

file(COPY cmb.png DESTINATION ${CMAKE_BINARY_DIR})

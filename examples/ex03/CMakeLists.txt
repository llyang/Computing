cmake_minimum_required(VERSION 3.10)
project(ex03)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

foreach(ex ascii_table calc-0.1 calc-0.2 calc-0.3 calc-0.4 my_sqrt pi_Archimedes_inner pi_Liu_inner prime_Eratosthenes sort_vector_double square_table_for square_table_while vector_numbers vector_words)
  add_executable(${ex}.exe ${ex}.cpp)
endforeach(ex)



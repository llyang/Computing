CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: square_table_while.exe square_table_for.exe ascii_table.exe \
  pi_Archimedes_inner.exe pi_Liu_inner.exe \
  prime_Eratosthenes.exe \
  vector_numbers.exe vector_words.exe sort_vector_double.exe \
  my_sqrt.exe \
  calc-0.1.exe calc-0.2.exe calc-0.3.exe calc-0.4.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

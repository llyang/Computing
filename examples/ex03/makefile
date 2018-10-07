CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: square_table_while.exe square_table_for.exe ascii_table.exe \
  pi_Archimedes_inner.exe pi_Liu_inner.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

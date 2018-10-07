CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: square_table_while.exe square_table_for.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

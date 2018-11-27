CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all clean

default: all

all: test_scope.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

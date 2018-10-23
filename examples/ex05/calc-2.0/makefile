CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: calc-2.0.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

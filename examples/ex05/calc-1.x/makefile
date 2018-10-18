CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: calc-1.0.exe calc-1.1.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

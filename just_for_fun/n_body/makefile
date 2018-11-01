CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all clean

default: all

all: calc_2body.exe calc_3body.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: ex02a.exe ex02b.exe ex02c.exe ex02d.exe ex02e.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

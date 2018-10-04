CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: ex02a.exe ex02b.exe ex02c.exe ex02d.exe ex02e.exe ex02f.exe ex02g.exe ex02h.exe ex02i.exe ex02j.exe ex02k.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

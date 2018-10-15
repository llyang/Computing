CXX = g++
CXXFLAGS = -std=c++11 

.PHONY: default all

default: all

all: vector_error.exe sqrt_error.exe sqrt_nan.exe \
  sqrt_exception.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.exe

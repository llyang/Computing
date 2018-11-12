CXX = g++
CXXFLAGS = -std=c++11

.PHONY: default all clean

default: all

all: test_complex.exe

OBJECTS = Complex.o
HEADERS = Complex.h

.PRECIOUS: %.o

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

clean:
	$(RM) *.o *.exe

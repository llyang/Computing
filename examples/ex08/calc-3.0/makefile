CXX = g++
CXXFLAGS = -std=c++11

.PHONY: default all clean

default: all

all: calc-3.0.exe

OBJECTS = Token_stream.o Calculator.o Variable.o
HEADERS = Token.h Token_stream.h Calculator.h Variable.h

.PRECIOUS: %.o

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

clean:
	$(RM) *.o *.exe

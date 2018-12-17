CXX = g++
CXXFLAGS = -g -std=c++11

.PHONY: all clean

all: test_vector.exe

OBJECTS = Vector.o
HEADERS = Vector.h

.PRECIOUS: %.o

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

clean:
	$(RM) *.o *.exe

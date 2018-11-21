CXX = g++
CXXFLAGS = -std=c++11

.PHONY: all clean

all: test_ps.exe test_csv.exe

.PRECIOUS: %.o

OBJECTS = Punct_stream.o
HEADERS = Punct_stream.h

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

clean:
	$(RM) *.o *.exe

CXX = g++
CXXFLAGS = -std=c++11

.PHONY: all clean

all: read_vectors.exe 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe

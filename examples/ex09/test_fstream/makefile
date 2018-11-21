CXX = g++
CXXFLAGS = -std=c++11

all: test_fstream.exe 

.PHONY: all clean

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe

CXX = g++
CXXFLAGS = -std=c++11

.PHONY: all clean

all: test_sstream.exe 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe

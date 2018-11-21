CXX = g++
CXXFLAGS = -std=c++11

.PHONY: all clean

all: read_int.exe read_int_new.exe

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe

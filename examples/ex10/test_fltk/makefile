CXX = g++
CXXFLAGS = -g -std=c++11 $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --ldflags)

test_fltk.exe: test_fltk.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.exe *.o *.dSYM


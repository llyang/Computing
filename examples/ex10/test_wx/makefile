CXX = g++
CXXFLAGS = -g -std=c++11 $(shell wx-config --cxxflags)
LDFLAGS = $(shell wx-config --libs)

test_wx.exe: test_wx.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.exe *.o *.dSYM


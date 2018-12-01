CXX = g++
CXXFLAGS = -std=c++11 $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --use-images --ldflags)

.PHONY: default all clean

.SUFFIXES: .cpp .o

TARGETS = calc-4.0.exe

default: all

all: $(TARGETS)

OBJECTS = Token_stream.o Calculator.o Variable.o
HEADERS = Token.h Token_stream.h Calculator.h Variable.h

GRAPHLIB = GUI.o Graph.o Window.o
GRAPHINC = GUI.h Graph.h Point.h Simple_window.h Window.h fltk.h

.PRECIOUS: %.o

%.exe: %.o $(OBJECTS) $(HEADERS) $(GRAPHLIB) $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS) $(GRAPHLIB) $(LDFLAGS)

%.o: %.cpp $(HEADERS) $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGETS) $(OBJECTS) $(GRAPHLIB) *.dSYM


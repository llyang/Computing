CXX = g++
CXXFLAGS = -std=c++11 $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --use-images --ldflags)

.PHONY: default all clean

.SUFFIXES: .cpp .o

TARGETS = test.exe test_move.exe test_automove.exe test_keyboard.exe test_vector_ref.exe test_animation.exe test_thread.exe

default: all

all: $(TARGETS)

GRAPHLIB = GUI.o Graph.o Window.o
GRAPHINC = GUI.h Graph.h Point.h Simple_window.h Window.h fltk.h Vector_ref.h

.PRECIOUS: %.o

%.exe: %.o $(GRAPHLIB) $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(GRAPHLIB) $(LDFLAGS)

%.o: %.cpp $(GRAPHINC)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf *.exe *.o *.dSYM


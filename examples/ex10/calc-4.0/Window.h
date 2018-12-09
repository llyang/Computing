#ifndef WINDOW_GUARD
#define WINDOW_GUARD 1

#include <string>
#include <vector>

#include "fltk.h"

#include "Point.h"

namespace Graph_lib {

class Shape; // "forward declare" Shape
class Widget;

class Window : public Fl_Window {
public:
  Window(int w, int h, const std::string& title); // let the system pick the location
  Window(Point xy, int w, int h, const std::string& title); // top left corner in xy
  virtual ~Window() {}

  int x_max() const { return w; }
  int y_max() const { return h; }

  using Fl_Window::resize; // resize(int x, int y, int w, int h);

  void resize(int ww, int hh);

  void set_label(const std::string& s) { label(s.c_str()); }

  // create and attach widget
  // this function should only be called ONCE for each widget
  void attach(Widget& w);

  void attach(Shape& s); // add s to shapes
  void detach(Shape& s); // remove s from shapes
  void put_on_top(Shape& p); // put p on top of other shapes

protected:
  void draw();

private:
  std::vector<Shape*> shapes; // shapes attached to window
  int w, h; // window size

  void init();
};

int gui_main(); // invoke GUI library's main event loop

inline int x_max() { return Fl::w(); } // width of screen in pixels
inline int y_max() { return Fl::h(); } // height of screen in pixels

} // namespace Graph_lib
#endif

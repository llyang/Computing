#ifndef WINDOW_GUARD
#define WINDOW_GUARD 1

#include <string>
#include <vector>

#include "fltk.h"

#include "Graph.h"
#include "Point.h"

using Graph_lib::Color;

namespace Graph_lib {

class Widget;

class Window : public Fl_Double_Window {
public:
  using Super = Fl_Double_Window;
  // let the system pick the location
  Window(int w, int h, const std::string& title, bool resizable = true);
  // top left corner in xy
  Window(Point xy, int w, int h, const std::string& title, bool resizable = true);

  ~Window() override = default;

  int x_max() const { return w; }
  int y_max() const { return h; }

  using Super::resize; // resize(int x, int y, int w, int h);

  void resize(int ww, int hh);

  void set_background_color(Color c) { color(static_cast<Fl_Color>(c)); }
  void set_label(const std::string& s) { label(s.c_str()); }

  void attach(Widget& w); // attach a widget
  void detach(Widget& w); // hide the widget (not really detached)

  void attach(const Shape& s); // add s to shapes
  void detach(const Shape& s); // remove s from shapes
  void put_on_top(const Shape& p); // put p on top of other shapes
  void detach_all_shapes() { shapes.clear(); }

protected:
  void draw() override;

private:
  std::vector<const Shape*> shapes; // shapes attached to window
  int w, h; // window size

  void init(bool res);
};

int gui_main(); // invoke GUI library's main event loop

inline int x_max() { return Fl::w(); } // width of screen in pixels
inline int y_max() { return Fl::h(); } // height of screen in pixels

} // namespace Graph_lib
#endif

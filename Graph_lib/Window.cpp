#include <algorithm>
#include <string>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using std::string;

namespace Graph_lib {

Window::Window(int ww, int hh, const string& title)
    : Fl_Double_Window { ww, hh, title.c_str() }
    , w { ww }
    , h { hh }
{
  init();
}

Window::Window(Point xy, int ww, int hh, const string& title)
    : Fl_Double_Window { xy.x, xy.y, ww, hh, title.c_str() }
    , w { ww }
    , h { hh }
{
  init();
}

void Window::init()
{
  resizable(this);
  Fl::visual(FL_DOUBLE | FL_INDEX);
  show();
}

//----------------------------------------------------

void Window::resize(int ww, int hh)
{
  w = ww;
  h = hh;
  size(ww, hh);
}

void Window::draw()
{
  Fl_Window::draw();
  for (auto shape : shapes)
    shape->draw();
}

void Window::attach(Widget& w)
{
  begin(); // FTLK: begin attaching new Fl_Widgets to this window
  w.create_and_attach(*this); // let the Widget create its Fl_Widget
  end(); // FTLK: stop attaching new Fl_Widgets to this window
}

void Window::attach(Shape& s)
{
  // each shape should only be attached once
  detach(s);
  shapes.push_back(&s);
}

void Window::detach(Shape& s)
{
  auto it { std::find(shapes.begin(), shapes.end(), &s) };
  if (it != shapes.end()) {
    shapes.erase(it);
  }
}

void Window::put_on_top(Shape& s)
{
  attach(s);
}

int gui_main() { return Fl::run(); }

} // namespace Graph_lib

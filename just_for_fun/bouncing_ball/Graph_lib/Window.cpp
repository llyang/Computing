#include <algorithm>
#include <string>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using std::string;

namespace Graph_lib {

Window::Window(int ww, int hh, const string& title, bool resizable)
    : Super { ww, hh, title.c_str() }
    , w { ww }
    , h { hh }
{
  init(resizable);
}

Window::Window(Point xy, int ww, int hh, const string& title, bool resizable)
    : Super { xy.x, xy.y, ww, hh, title.c_str() }
    , w { ww }
    , h { hh }
{
  init(resizable);
}

void Window::init(bool res)
{
  if (res)
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
  Super::draw();
  for (auto shape : shapes)
    shape->draw();
}

void Window::attach(Widget& w)
{
  begin(); // FTLK: begin attaching new Fl_Widgets to this window
  w.attach(*this); // let the Widget create its Fl_Widget
  end(); // FTLK: stop attaching new Fl_Widgets to this window
}

void Window::detach(Widget& w)
{
  w.hide();
}

void Window::attach(const Shape& s)
{
  // each shape should only be attached once
  detach(s);
  shapes.push_back(&s);
}

void Window::detach(const Shape& s)
{
  auto it { std::find(shapes.begin(), shapes.end(), &s) };
  if (it != shapes.end()) {
    shapes.erase(it);
  }
}

void Window::put_on_top(const Shape& s)
{
  attach(s);
}

int gui_main() { return Fl::run(); }

} // namespace Graph_lib

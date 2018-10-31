#include <cmath>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using std::string;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  int x;
  int y;
  Graph_lib::Circle ball;

  // callback for quit_button
  static void cb_quit(void*, void* pw)
  {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  bool handle_keydown(int key);

  bool handle_mousepush(int button, int ex, int ey);

  int handle(int event);
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 },
      70, 20, "Quit", cb_quit }
    , x { x_max() / 2 }
    , y { y_max() / 2 }
    , ball { Point { x, y }, 5 }
{
  attach(quit_button);
  ball.set_style(Line_style { Line_style::solid, 4 });
  ball.set_fill_color(Color::red);
  ball.set_color(Color::red);
  attach(ball);
}

bool My_window::handle_keydown(int key)
{
  bool ret { false };
  constexpr int d { 5 };
  switch (key) {
  case FL_Up:
    ball.move(0, -d);
    y -= d;
    ret = true;
    break;
  case FL_Down:
    ball.move(0, d);
    y += d;
    ret = true;
    break;
  case FL_Left:
    ball.move(-d, 0);
    x -= d;
    ret = true;
    break;
  case FL_Right:
    ball.move(d, 0);
    x += d;
    ret = true;
    break;
  }
  if (ret)
    Fl::redraw();
  return ret;
}

bool My_window::handle_mousepush(int button, int ex, int ey)
{
  if (button != FL_LEFT_MOUSE)
    return false;
  ball.move(ex - x, ey - y);
  x = ex;
  y = ey;
  Fl::redraw();
  return true;
}

int My_window::handle(int event)
{
  int ret { Fl_Window::handle(event) };
  if (ret == 1)
    return ret;
  switch (event) {
  case FL_FOCUS:
  case FL_UNFOCUS:
    ret = 1;
    break;
  case FL_KEYDOWN:
    if (handle_keydown(Fl::event_key()))
      ret = 1;
    break;
  case FL_PUSH:
    if (handle_mousepush(Fl::event_button(), Fl::event_x(), Fl::event_y()))
      ret = 1;
    break;
  }
  return ret;
}

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Move a ball" };

  return Graph_lib::gui_main();
}

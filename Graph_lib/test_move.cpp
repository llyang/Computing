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
  Graph_lib::Button next_button;
  int center_x;
  int center_y;
  int radius;
  double phi;
  double x;
  double y;
  Graph_lib::Circle ball;

  double new_x() const { return center_x + radius * cos(phi); }
  double new_y() const { return center_y + radius * sin(phi); }

  // callback for quit_button
  static void cb_quit(void*, void* pw)
  {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  // callback for next_button
  static void cb_next(void*, void* pw)
  {
    static_cast<My_window*>(pw)->next();
  }

  void next();
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
    , next_button { Point { x_max() - 70, 20 }, 70, 20, "Next", cb_next }
    , center_x { 300 }
    , center_y { 200 }
    , radius { 100 }
    , phi { 0 }
    , x { new_x() }
    , y { new_y() }
    , ball { Point { int(x), int(y) }, 5 }
{
  attach(quit_button);
  attach(next_button);
  ball.set_style(Line_style { Line_style::solid, 4 });
  ball.set_fill_color(Color { Color::red });
  ball.set_color(Color { Color::red });
  attach(ball);
}

void My_window::next()
{
  constexpr double dphi { 0.1 };
  phi += dphi;
  ball.move(new_x() - x, new_y() - y);
  x = new_x();
  y = new_y();
  Fl::redraw();
}

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Move a ball" };

  return Graph_lib::gui_main();
}

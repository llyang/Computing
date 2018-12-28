#include <cmath>

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

using std::string;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

////////////////////////////////////////

constexpr double ball_speed { -0.1 };
constexpr int rotation_radius { 100 };
const Point rotation_center { 300, 200 };

class Ball {

public:
  Ball()
      : c { Point { rotation_center.x + rotation_radius, rotation_center.y }, 10 }
      , phi { 0 }
      , speed { ball_speed }
  {
    c.set_line_style(Line_style { 1, Color::red });
    c.set_fill_color(Color::red);
  }

  const Graph_lib::Shape* get_shape() const { return &c; }

  void move()
  {
    phi += speed;
    int new_x { static_cast<int>(rotation_center.x + rotation_radius * cos(phi)) };
    int new_y { static_cast<int>(rotation_center.y + rotation_radius * sin(phi)) };
    Point center { c.center() };
    c.move(new_x - center.x, new_y - center.y);
  }

private:
  Graph_lib::Circle c;
  double phi;
  double speed;
};

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button next_button;
  Graph_lib::Circle circ;
  Ball ball;

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
    , circ { rotation_center, rotation_radius }
{
  attach(quit_button);
  attach(next_button);
  attach(circ);
  attach(*(ball.get_shape()));
}

void My_window::next()
{
  ball.move();
  redraw();
}

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Move a ball" };

  return Graph_lib::gui_main();
}

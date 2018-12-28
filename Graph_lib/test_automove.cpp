#include <cmath>

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

using std::string;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

////////////////////////////////////////

constexpr int fps { 15 };
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

  void start()
  {
    speed = ball_speed;
  }

  void stop()
  {
    speed = 0;
  }

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

////////////////////////////////////////

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button stop_button;
  Graph_lib::Circle circ;
  Ball ball;
  bool started;

  void quit() { hide(); }

  void loop()
  {
    ball.move();
    redraw();
    Fl::repeat_timeout(1. / fps, cb_timeout, this);
  }

  static void cb_timeout(void* pw) { static_cast<My_window*>(pw)->loop(); }

  void stop()
  {
    if (started) {
      stop_button.set_label("Start");
      ball.stop();
    } else {
      stop_button.set_label("Stop");
      ball.start();
    }
    started = !started;
  }
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit",
      [](void*, void* pw) { static_cast<My_window*>(pw)->quit(); } }
    , stop_button { Point { x_max() - 70, 20 }, 70, 20, "Stop",
      [](void*, void* pw) { static_cast<My_window*>(pw)->stop(); } }
    , circ { rotation_center, rotation_radius }
    , started { true }
{
  attach(quit_button);
  attach(stop_button);
  attach(circ);
  attach(*(ball.get_shape()));
  Fl::add_timeout(1. / fps, cb_timeout, this);
}

////////////////////////////////////////

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Move a ball" };

  return Graph_lib::gui_main();
}

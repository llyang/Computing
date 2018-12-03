#include <cmath>
#include <utility>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using std::pair;
using std::string;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

////////////////////////////////////////

class Moving_ball {

public:
  Moving_ball(int r, double phi0, double dphi0)
      : radius { r }
      , phi { phi0 }
      , dphi { dphi0 }
      , x { new_x() }
      , y { new_y() }
  {
  }

  pair<double, double> move();

private:
  int radius;
  double phi;
  double dphi;
  double x;
  double y;

  double new_x() const { return radius * cos(phi); }
  double new_y() const { return radius * sin(phi); }
};

pair<double, double> Moving_ball::move()
{
  phi += dphi;
  double dx { new_x() - x };
  double dy { new_y() - y };
  x = new_x();
  y = new_y();
  return pair<double, double> { dx, dy };
}

////////////////////////////////////////

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button stop_button;
  Moving_ball ball;
  Graph_lib::Circle circ;
  bool started;

  static constexpr double step { 0.1 };

  void quit() { hide(); }

  void next();

  void timeout()
  {
    next();
    Fl::repeat_timeout(step, cb_timeout, this);
  }

  static void cb_timeout(void* pw) { static_cast<My_window*>(pw)->timeout(); }

  void manage_timeout()
  {
    if (started) {
      Fl::add_timeout(step, cb_timeout, this);
    } else {
      Fl::remove_timeout(cb_timeout, this);
    }
  }

  void stop()
  {
    if (started)
      stop_button.set_label("Start");
    else
      stop_button.set_label("Stop");
    started = !started;
    manage_timeout();
  }
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit",
      [](void*, void* pw) { static_cast<My_window*>(pw)->quit(); } }
    , stop_button { Point { x_max() - 70, 20 }, 70, 20, "Stop",
      [](void*, void* pw) { static_cast<My_window*>(pw)->stop(); } }
    , ball { 100, 0, 0.1 }
    , circ { Point { 400, 200 }, 5 }
    , started { true }
{
  attach(quit_button);
  attach(stop_button);
  circ.set_style(Line_style { Line_style::solid, 4 });
  circ.set_fill_color(Color::red);
  circ.set_color(Color::red);
  attach(circ);
  manage_timeout();
}

void My_window::next()
{
  pair<double, double> dxdy { ball.move() };
  circ.move(dxdy.first, dxdy.second);
  Fl::redraw();
}

////////////////////////////////////////

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Move a ball" };

  return Graph_lib::gui_main();
}


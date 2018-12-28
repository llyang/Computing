#include <string>

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

using std::string;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

////////////////////////////////////////

constexpr int fps { 30 };
constexpr int ball_speed { 5 };

class Ball {

public:
  Ball()
      : c { Point { 200, 200 }, 10 }
      , speed_x { 0 }
      , speed_y { 0 }
  {
    c.set_line_style(Line_style { 1, Color::red });
    c.set_fill_color(Color::red);
  }

  void set_speed_x(int speed)
  {
    if (speed > 0)
      speed_x = ball_speed;
    else if (speed < 0)
      speed_x = -ball_speed;
    else
      speed_x = 0;
  }

  void set_speed_y(int speed)
  {
    if (speed > 0)
      speed_y = ball_speed;
    else if (speed < 0)
      speed_y = -ball_speed;
    else
      speed_y = 0;
  }

  const Graph_lib::Shape* get_shape() const { return &c; }

  void move()
  {
    c.move(speed_x, speed_y);
  }

  void move_to(int x, int y)
  {
    Point p { c.center() };
    c.move(x - p.x, y - p.y);
  }

private:
  Graph_lib::Circle c;
  int speed_x;
  int speed_y;
};

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Ball ball;

  // callback for quit_button
  static void cb_quit(void*, void* pw)
  {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  void loop()
  {
    ball.move();
    redraw();
    Fl::repeat_timeout(1. / fps, cb_timeout, this);
  }

  static void cb_timeout(void* pw) { static_cast<My_window*>(pw)->loop(); }

  bool handle_keydown(int key);
  bool handle_keyup(int key);
  bool handle_mousepush(int button, int ex, int ey);

  int handle(int event) override;
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
{
  attach(quit_button);
  attach(*(ball.get_shape()));
  Fl::add_timeout(1. / fps, cb_timeout, this);
}

bool My_window::handle_keydown(int key)
{
  bool ret { false };
  switch (key) {
  case FL_Up:
    ball.set_speed_y(-1);
    ret = true;
    break;
  case FL_Down:
    ball.set_speed_y(1);
    ret = true;
    break;
  case FL_Left:
    ball.set_speed_x(-1);
    ret = true;
    break;
  case FL_Right:
    ball.set_speed_x(1);
    ret = true;
    break;
  }
  if (ret)
    redraw();
  return ret;
}

bool My_window::handle_keyup(int key)
{
  bool ret { false };
  switch (key) {
  case FL_Up:
  case FL_Down:
    ball.set_speed_y(0);
    ret = true;
    break;
  case FL_Left:
  case FL_Right:
    ball.set_speed_x(0);
    ret = true;
    break;
  }
  if (ret)
    redraw();
  return ret;
}

bool My_window::handle_mousepush(int button, int ex, int ey)
{
  if (button != FL_LEFT_MOUSE)
    return false;
  ball.move_to(ex, ey);
  redraw();
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
  case FL_KEYUP:
    if (handle_keyup(Fl::event_key()))
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

#include "Paddle.h"
#include "constants.h"

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;
using Graph_lib::Stroke;

Paddle::Paddle()
    : r { Point { init_x, init_y }, w, h }
    , speed_x { 0 }
{
  r.set_line_style(Line_style { 1, Color::blue, Stroke::solid });
  r.set_fill_color(Color::blue);
}

void Paddle::reset()
{
  int x { r.point(0).x };
  r.move(init_x - x, 0);
  speed_x = 0;
}

void Paddle::set_speed(int speed)
{
  if (speed > 0)
    speed_x = default_speed;
  else if (speed < 0)
    speed_x = -default_speed;
  else
    speed_x = 0;
}

void Paddle::move()
{
  int x { r.point(0).x };
  if ((x > 0 && speed_x < 0) || (x + w < window_width && speed_x > 0))
    r.move(speed_x, 0);
};
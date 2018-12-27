#include "Ball.h"
#include "constants.h"

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;
using Graph_lib::Stroke;

Ball::Ball()
    : c { Point { init_x, init_y }, r }
    , speed_x { default_speed }
    , speed_y { default_speed }
{
  c.set_line_style(Line_style { 1, Color::red, Stroke::solid });
  c.set_fill_color(Color::red);
}

void Ball::reset()
{
  Point p { c.center() };
  c.move(init_x - p.x, init_y - p.y);
  speed_x = default_speed;
  speed_y = default_speed;
}

void Ball::move()
{
  c.move(speed_x, speed_y);
  Point p { c.center() };
  if (p.x - r <= 0 || p.x + r >= window_width) {
    speed_x = -speed_x;
  }
  if (p.y - r <= 0 || p.y + r >= window_height) {
    speed_y = -speed_y;
  }
};

using Graph_lib::Rectangle;

bool Ball::collide(const Graph_lib::Rectangle& rect)
{
  // just for illustration, definitely not the correct way to detect collision

  int upper { rect.point(0).y };
  int lower { upper + rect.height() };
  int left { rect.point(0).x };
  int right { left + rect.width() };

  int x { c.center().x };
  int y { c.center().y };
  int r { c.radius() };

  if (x >= left && x <= right) {
    if ((y < upper && upper - y <= r) || (y > lower && y - lower <= r)) {
      speed_y = -speed_y;
      return true;
    }
  }

  if (y >= upper && y <= lower) {
    if ((x < left && left - x <= r) || (x > right && x - right <= r)) {
      speed_x = -speed_x;
      return true;
    }
  }

  return false;
}

void Ball::collide(const Paddle& paddle)
{
  auto rect { dynamic_cast<const Rectangle*>(paddle.get_shape()) };
  collide(*rect);
}

void Ball::collide(Block& block)
{
  auto rect { dynamic_cast<const Rectangle*>(block.get_shape()) };
  if (collide(*rect))
    block.die();
}
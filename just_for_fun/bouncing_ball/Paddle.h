#ifndef _PADDLE_H
#define _PADDLE_H

#include "Graph_lib/Graph.h"
#include "constants.h"

class Paddle {
public:
  Paddle();

  void reset();

  void move();

  void set_speed(int speed);

  const Graph_lib::Shape* get_shape() const { return &r; }

private:
  Graph_lib::Rectangle r;
  int speed_x;
  static constexpr int w { 100 };
  static constexpr int h { 20 };
  static constexpr int init_x { window_width / 2 - w };
  static constexpr int init_y { window_height - h };
  static constexpr int default_speed { 10 };
};

#endif

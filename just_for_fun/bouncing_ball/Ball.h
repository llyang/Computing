#ifndef _BALL_H
#define _BALL_H

#include "Graph_lib/Graph.h"

#include "Block.h"
#include "Paddle.h"

class Ball {
public:
  Ball();

  void reset();

  void move();

  const Graph_lib::Shape* get_shape() const { return &c; }

  void collide(const Paddle& paddle);
  void collide(Block& block);

private:
  bool collide(const Graph_lib::Rectangle& rect);

private:
  Graph_lib::Circle c;
  int speed_x;
  int speed_y;
  static constexpr int init_x { 200 };
  static constexpr int init_y { 400 };
  static constexpr int r { 10 };
  static constexpr int default_speed { 5 };
};

#endif

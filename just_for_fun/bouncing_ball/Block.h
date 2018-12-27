#ifndef _BLOCK_H
#define _BLOCK_H

#include "Graph_lib/Graph.h"
#include "constants.h"

class Block {
public:
  Block(int x, int y);

  bool is_alive() { return alive; }

  void reset()
  {
    alive = true;
    r.set_fill_visibility(true);
  }

  void die()
  {
    alive = false;
    r.set_fill_visibility(false);
  }

  const Graph_lib::Shape* get_shape() const { return &r; }

private:
  Graph_lib::Rectangle r;
  bool alive;
};

#endif

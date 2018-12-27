#include "Block.h"
#include "constants.h"

using Graph_lib::Color;
using Graph_lib::Point;

Block::Block(int x, int y)
    : r { Point { x, y }, block_width, block_height }
    , alive { true }
{
  r.set_line_color(background);
  r.set_fill_color(Color::magenta);
}

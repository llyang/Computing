#include "Graph_lib/Graph.h"
#include "Graph_lib/Simple_window.h"
#include "Graph_lib/Vector_ref.h"

using Graph_lib::Color;
using Graph_lib::Point;

int main()
{
  Simple_window win { Point { 100, 100 }, 600, 400, "Colors" };

  Graph_lib::Vector_ref<Graph_lib::Rectangle> vr;

  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      vr.push_back(new Graph_lib::Rectangle { Point { i * 20, j * 20 }, 20, 20 });
      vr[vr.size() - 1].set_fill_color(static_cast<Color>(i * 16 + j));
      win.attach(vr[vr.size() - 1]);
    }
  }

  return Graph_lib::gui_main();
}

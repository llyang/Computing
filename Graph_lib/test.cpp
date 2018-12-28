#include <sstream>

#include "Graph_lib/Graph.h"
#include "Graph_lib/Simple_window.h"

using std::ostringstream;

using Graph_lib::Color;
using Graph_lib::Fill_style;
using Graph_lib::Font;
using Graph_lib::Line_style;
using Graph_lib::Stroke;
using Graph_lib::Text_style;

using Graph_lib::Point;

void cb_funny(void*, void* pw);

int main()
{
  Simple_window win { Point { 100, 100 }, 800, 600, "Some shapes" };

  Graph_lib::Line line { Point { 50, 50 }, Point { 100, 100 } };
  line.set_line_style(Line_style { 4, Color::blue });
  win.attach(line);

  //Graph_lib::Lines lines;
  Graph_lib::Lines lines { Point { 50, 100 }, Point { 60, 40 } };
  lines.add(Point { 70, 90 }, Point { 50, 40 });
  lines.set_line_style(Line_style { 4, Color::yellow, Stroke::dash });
  win.attach(lines);

  Graph_lib::Rectangle rect { Point { 200, 200 }, 100, 50 };
  rect.set_line_style(Line_style { 4, Color::blue });
  rect.set_fill_color(Color::green);
  win.attach(rect);

  //Graph_lib::Open_polyline pl { Point { 50, 300 }, Point { 100, 350 } };
  //Graph_lib::Closed_polyline pl { Point { 50, 300 }, Point { 100, 350 } };
  Graph_lib::Marked_polyline pl { "o" };
  pl.add(Point { 60, 400 });
  pl.add(Point { 70, 300 });
  pl.add(Point { 80, 400 });
  pl.set_line_style(Line_style { 4, Color::dark_magenta });
  pl.set_fill_color(Color::dark_yellow);
  win.attach(pl);

  Graph_lib::Marks marks { "x" };
  marks.add(Point { 60, 450 });
  marks.add(Point { 70, 500 });
  marks.add(Point { 60, 500 });
  win.attach(marks);

  win.wait_for_next();

  Graph_lib::Mark m { Point { 100, 200 }, 'x' };
  win.attach(m);

  Graph_lib::Circle c { Point { 100, 200 }, 50 };
  win.attach(c);

  Graph_lib::Ellipse e { Point { 100, 200 }, 75, 25 };
  win.attach(e);

  Graph_lib::Text t { Point { 150, 150 }, "Hello, world!" };
  t.set_text_style(Text_style { 20, Color::dark_red, Font::times_bold });
  win.attach(t);

  ostringstream oss;
  oss << "screen size: " << Graph_lib::x_max() << "*" << Graph_lib::y_max()
      << "; window size: " << win.x_max() << "*" << win.y_max();
  Graph_lib::Text sizes { Point { 100, 20 }, oss.str() };
  win.attach(sizes);

  Graph_lib::Polygon poly;
  poly.add(Point { 300, 200 });
  poly.add(Point { 350, 100 });
  poly.add(Point { 400, 200 });
  poly.set_line_style(Line_style { 4, Color::red, Stroke::dash });
  poly.set_fill_color(Color::cyan);
  win.attach(poly);

  win.wait_for_next();

  Graph_lib::Image wrong { Point { 250, 100 }, "cmb.ha" };
  win.attach(wrong);

  Graph_lib::Image ii { Point { 350, 250 }, "cmb.png" };
  win.attach(ii);

  win.wait_for_next();

  ii.move(-100, -100);

  win.wait_for_next();

  win.put_on_top(rect);

  win.wait_for_next();

  win.put_on_top(poly);

  win.wait_for_next();

  win.detach(ii);

  win.wait_for_next();

  win.attach(ii);

  win.wait_for_next();

  Graph_lib::Button button { Point { 600, 400 }, 70, 20, "Funny", cb_funny };
  Graph_lib::In_box inbox { Point { 600, 430 }, 100, 20, "haha" };
  Graph_lib::Out_box outbox { Point { 600, 460 }, 100, 20, "hehe" };

  win.attach(button);
  win.attach(inbox);
  win.attach(outbox);

  win.wait_for_next();

  button.hide();

  win.wait_for_next();

  button.show();

  return Graph_lib::gui_main();
}

void cb_funny(void*, void*)
{
}

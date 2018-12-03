#include <sstream>

#include "Graph.h"
#include "Simple_window.h"

using std::ostringstream;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

void cb_funny(void*, void* pw);

int main()
{
  Simple_window win { Point { 100, 100 }, 600, 400, "Some shapes" };

  Graph_lib::Polygon poly;
  poly.add(Point { 300, 200 });
  poly.add(Point { 350, 100 });
  poly.add(Point { 400, 200 });
  poly.set_color(Color::red);
  poly.set_style(Line_style { Line_style::dash, 4 });
  win.attach(poly);

  Graph_lib::Rectangle rect { Point { 200, 200 }, 100, 50 };
  rect.set_color(Color::blue);
  rect.set_style(Line_style { Line_style::solid, 4 });
  rect.set_fill_color(Color::green);
  win.attach(rect);

  Graph_lib::Text t { Point { 150, 150 }, "Hello, world!" };
  t.set_font(Graph_lib::Font::times_bold);
  t.set_font_size(20);
  t.set_color(Color::dark_red);
  win.attach(t);

  win.wait_for_next();

  Graph_lib::Image ii { Point { 350, 250 }, "cmb.png" };
  win.attach(ii);

  Graph_lib::Circle c { Point { 100, 200 }, 50 };
  win.attach(c);

  Graph_lib::Ellipse e { Point { 100, 200 }, 75, 25 };
  win.attach(e);

  Graph_lib::Mark m { Point { 100, 200 }, 'x' };
  win.attach(m);

  ostringstream oss;
  oss << "screen size: " << Graph_lib::x_max() << "*" << Graph_lib::y_max()
      << "; window size: " << win.x_max() << "*" << win.y_max();
  Graph_lib::Text sizes { Point { 100, 20 }, oss.str() };
  win.attach(sizes);

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

  Graph_lib::Button button { Point { 100, 100 }, 70, 20, "Funny", cb_funny };

  win.attach(button);

  win.wait_for_next();

  button.hide();

  win.wait_for_next();

  button.show();

  win.wait_for_next();

  return Graph_lib::gui_main();
}

void cb_funny(void*, void* pw)
{
}

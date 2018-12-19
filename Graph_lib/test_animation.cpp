#include <iostream>
#include <string>
#include <vector>

#include "GUI.h"
#include "Graph.h"
#include "Vector_ref.h"
#include "Window.h"

using std::string;
using std::vector;

using Graph_lib::Color;
using Graph_lib::Line_style;
using Graph_lib::Point;

////////////////////////////////////////

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button stop_button;

  Graph_lib::Vector_ref<Graph_lib::Rectangle> vr;
  Graph_lib::Vector_ref<Graph_lib::Text> vt;

  bool started;

  static constexpr double step { 1. / 30. };

private:
  void create_grid();

  void quit() { hide(); }

  void next();

  void timeout()
  {
    next();
    Fl::repeat_timeout(step, cb_timeout, this);
  }

  static void cb_timeout(void* pw) { static_cast<My_window*>(pw)->timeout(); }

  void manage_timeout()
  {
    if (started) {
      Fl::add_timeout(step, cb_timeout, this);
    } else {
      Fl::remove_timeout(cb_timeout, this);
    }
  }

  void stop()
  {
    if (started)
      stop_button.set_label("Start");
    else
      stop_button.set_label("Stop");
    started = !started;
    manage_timeout();
  }
};

void My_window::create_grid()
{
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      vr.push_back(new Graph_lib::Rectangle { Point { i * 20, j * 20 }, 20, 20 });
      vr[vr.size() - 1].set_fill_color(i * 16 + j);
      attach(vr[vr.size() - 1]);
    }
  }
  const vector<string> vs { "haha", "hehe", "hihi", "hoho", "huhu" };
  for (auto& s : vs) {
    vt.push_back(new Graph_lib::Text { Point { 400, 50 + vt.size() * 30 }, s });
    Graph_lib::Text& t { vt[vt.size() - 1] };
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(20);
    t.set_color(Color::dark_red);
    attach(t);
  }
}

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit",
      [](void*, void* pw) { static_cast<My_window*>(pw)->quit(); } }
    , stop_button { Point { x_max() - 70, 20 }, 70, 20, "Stop",
      [](void*, void* pw) { static_cast<My_window*>(pw)->stop(); } }
    , started { true }
{
  attach(quit_button);
  attach(stop_button);

  create_grid();

  manage_timeout();
}

void My_window::next()
{
  Color c { vr[vr.size() - 1].fill_color() };
  for (int i = vr.size() - 1; i > 0; --i) {
    vr[i].set_fill_color(vr[i - 1].fill_color());
  }
  vr[0].set_fill_color(c);

  string s { vt[vt.size() - 1].label() };
  for (int i = vt.size() - 1; i > 0; --i) {
    vt[i].set_label(vt[i - 1].label());
  }
  vt[0].set_label(s);

  redraw();
}

////////////////////////////////////////

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "animation" };

  return Graph_lib::gui_main();
}


#include <sstream>
#include <stdexcept>

#include "Calculator.h"

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

using std::exception;
using std::istringstream;
using std::ostringstream;
using std::string;

using Graph_lib::Point;

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button calc_button;
  Graph_lib::In_box inbox;
  Graph_lib::Out_box outbox;
  istringstream iss;
  Calc::Calculator calc;

  // callback for quit_button
  static void cb_quit(void*, void* pw)
  {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  // callback for calc_button
  static void cb_calc(void*, void* pw)
  {
    static_cast<My_window*>(pw)->do_calc();
  }

  void do_calc();
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
    , calc_button { Point { 255, 50 }, 80, 20, "Calculate", cb_calc }
    , inbox { Point { 50, 50 }, 200, 20, "" }
    , outbox { Point { 50, 100 }, 200, 20, "" }
    , calc { iss }
{
  attach(quit_button);
  attach(calc_button);
  attach(inbox);
  attach(outbox);
}

void My_window::do_calc()
{
  string s { inbox.get_string() };
  iss.str(s + ";");
  iss.clear();
  try {
    ostringstream oss;
    oss << calc.calculate1();
    outbox.put(oss.str());
  } catch (exception& e) {
    outbox.put(e.what());
  }
}

int main()
{
  My_window win { Point { 100, 100 }, 600, 400, "Calculator" };

  return Graph_lib::gui_main();
}

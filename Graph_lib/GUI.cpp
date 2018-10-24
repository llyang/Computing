#include <sstream>

#include "GUI.h"

using std::string;

namespace Graph_lib {

void Button::attach(Window &win) {
  pw = new Fl_Button{loc.x, loc.y, width, height, label.c_str()};
  pw->callback(reinterpret_cast<Fl_Callback *>(do_it), &win); // pass the window
  own = &win;
}

int In_box::get_int() {
  const char *p = static_cast<Fl_Input *>(pw)->value();
  if (!isdigit(p[0]))
    return -999999;
  return atoi(p);
}

string In_box::get_string() {
  return string{static_cast<Fl_Input *>(pw)->value()};
}

void In_box::attach(Window &win) {
  pw = new Fl_Input{loc.x, loc.y, width, height, label.c_str()};
  own = &win;
}

void Out_box::put(int i) {
  std::stringstream ss;
  ss << i;
  static_cast<Fl_Output *>(pw)->value(ss.str().c_str());
}

void Out_box::put(const string &s) {
  static_cast<Fl_Output *>(pw)->value(s.c_str());
}

void Out_box::attach(Window &win) {
  pw = new Fl_Output{loc.x, loc.y, width, height, label.c_str()};
  own = &win;
}

} // namespace Graph_lib

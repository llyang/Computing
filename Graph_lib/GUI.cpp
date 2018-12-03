#include <sstream>
#include <stdexcept>

#include "GUI.h"

using std::string;

namespace Graph_lib {

void Widget::move(int dx, int dy)
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  hide();
  pw->position(loc.x += dx, loc.y += dy);
  show();
}

void Widget::hide()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  pw->hide();
}

void Widget::show()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  pw->show();
}

void Widget::deactivate()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  pw->deactivate();
}

void Widget::activate()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  pw->activate();
}

////////////////////////////////////////////////////////////////////////////////

void Button::set_label(const string& s)
{
  label = s;
  if (pw)
    pw->label(label.c_str());
}

void Button::create_and_attach(Window& win)
{
  if (pw) {
    throw std::runtime_error { "Widget already created" };
  }
  pw = new Fl_Button { loc.x, loc.y, width, height, label.c_str() };
  pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
  own = &win;
}

////////////////////////////////////////////////////////////////////////////////

int In_box::get_int()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  const char* p = static_cast<Fl_Input*>(pw)->value();
  if (!isdigit(p[0]))
    return -999999;
  return atoi(p);
}

string In_box::get_string()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  return string { static_cast<Fl_Input*>(pw)->value() };
}

void In_box::create_and_attach(Window& win)
{
  if (pw) {
    throw std::runtime_error { "Widget already created" };
  }
  pw = new Fl_Input { loc.x, loc.y, width, height, label.c_str() };
  own = &win;
}

////////////////////////////////////////////////////////////////////////////////

void Out_box::put(int i)
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  std::stringstream ss;
  ss << i;
  static_cast<Fl_Output*>(pw)->value(ss.str().c_str());
}

void Out_box::put(const string& s)
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  static_cast<Fl_Output*>(pw)->value(s.c_str());
}

void Out_box::create_and_attach(Window& win)
{
  if (pw) {
    throw std::runtime_error { "Widget already created" };
  }
  pw = new Fl_Output { loc.x, loc.y, width, height, label.c_str() };
  own = &win;
}

} // namespace Graph_lib

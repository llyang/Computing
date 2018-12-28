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

void Widget::attach(Window& win)
{
  if (own) { // already attached
    if (own == &win) { // the same window, just show
      show();
      activate();
      return;
    } else {
      throw std::runtime_error { "Widget already attached to a different window" };
    }
  } else {
    create_and_attach(win);
  }
}

////////////////////////////////////////////////////////////////////////////////

void Button::set_label(string s)
{
  label = std::move(s);
  if (pw)
    pw->label(label.c_str());
}

void Button::create_and_attach(Window& win)
{
  pw = new Fl_Button { loc.x, loc.y, width, height, label.c_str() };
  pw->labelsize(label_size_);
  pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
  own = &win;
}

////////////////////////////////////////////////////////////////////////////////

string In_box::get_string()
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  return string { dynamic_cast<Fl_Input*>(pw)->value() };
}

void In_box::create_and_attach(Window& win)
{
  pw = new Fl_Input { loc.x, loc.y, width, height, label.c_str() };
  own = &win;
}

////////////////////////////////////////////////////////////////////////////////

void Out_box::put(const string& s)
{
  if (!pw) {
    throw std::runtime_error { "Widget not created yet" };
  }
  dynamic_cast<Fl_Output*>(pw)->value(s.c_str());
}

void Out_box::create_and_attach(Window& win)
{
  pw = new Fl_Output { loc.x, loc.y, width, height, label.c_str() };
  own = &win;
}

} // namespace Graph_lib

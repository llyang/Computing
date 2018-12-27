#ifndef GUI_GUARD
#define GUI_GUARD

#include "fltk.h"

#include "Graph.h"
#include "Point.h"
#include "Window.h"

namespace Graph_lib {

// FLTK's required function type for all callbacks
using Callback = void (*)(void*, void*);

class Widget {
  // Widget is a handle to a Fl_widget - it is *not* a Fl_widget
  // We try to keep our interface classes at arm's length from FLTK
public:
  Widget(Point xy, int w, int h, std::string s, Callback cb)
      : loc { xy }
      , width { w }
      , height { h }
      , label { std::move(s) }
      , do_it { cb }
      , own { nullptr }
      , pw { nullptr }
  {
  }

  // This function should NEVER be called directly by users
  // The users should call Window::attach(Widget&) instead
  virtual void attach(Window&);

  void move(int dx, int dy);
  void hide();
  void show();
  void deactivate();
  void activate();

  virtual ~Widget() { delete pw; }

  // don't copy Widgets
  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;

protected:
  Point loc;
  int width;
  int height;
  std::string label;
  Callback do_it;

  Window* own; // every Widget belongs to a Window
  Fl_Widget* pw;

protected:
  virtual void create_and_attach(Window&) = 0;
};

struct Button : Widget {
  Button(Point xy, int ww, int hh, std::string s, Callback cb, int label_size = 14)
      : Widget { xy, ww, hh, std::move(s), cb }
      , label_size_ { label_size }
  {
  }

  void set_label(std::string s);

protected:
  void create_and_attach(Window& win) override;

private:
  int label_size_;
};

struct In_box : Widget {
  In_box(Point xy, int w, int h, std::string s)
      : Widget { xy, w, h, std::move(s), nullptr }
  {
  }

  std::string get_string();

protected:
  void create_and_attach(Window& win) override;
};

struct Out_box : Widget {
  Out_box(Point xy, int w, int h, std::string s)
      : Widget { xy, w, h, std::move(s), nullptr }
  {
  }

  void put(const std::string&);

protected:
  void create_and_attach(Window& win) override;
};

} // namespace Graph_lib

#endif

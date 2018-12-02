#ifndef GUI_GUARD
#define GUI_GUARD

#include "fltk.h"

#include "Graph.h"
#include "Point.h"
#include "Window.h"

namespace Graph_lib {

// FLTK's required function type for all callbacks
typedef void (*Callback)(void*, void*);

class Widget {
  // Widget is a handle to a Fl_widget - it is *not* a Fl_widget
  // We try to keep our interface classes at arm's length from FLTK
public:
  Widget(Point xy, int w, int h, const std::string& s, Callback cb)
      : loc { xy }
      , width { w }
      , height { h }
      , label { s }
      , do_it { cb }
  {
  }

  virtual void move(int dx, int dy)
  {
    hide();
    pw->position(loc.x += dx, loc.y += dy);
    show();
  }
  virtual void hide() { pw->hide(); }
  virtual void show() { pw->show(); }
  virtual void attach(Window&) = 0; // each Widget define at least one action for a window

  Point loc;
  int width;
  int height;
  std::string label;
  Callback do_it;

  virtual ~Widget() {}

protected:
  Window* own; // every Widget belongs to a Window
  Fl_Widget* pw;

private:
  Widget& operator=(const Widget&) = delete; // don't copy Widgets
  Widget(const Widget&) = delete;
};

struct Button : Widget {
  Button(Point xy, int ww, int hh, const std::string& s, Callback cb)
      : Widget { xy, ww, hh, s, cb }
  {
  }
  void attach(Window& win) override;
  void set_label(const std::string& s)
  {
    label = s;
    if (pw)
      pw->label(label.c_str());
  }
};

struct In_box : Widget {
  In_box(Point xy, int w, int h, const std::string& s)
      : Widget { xy, w, h, s, 0 }
  {
  }
  int get_int();
  std::string get_string();
  void attach(Window& win) override;
};

struct Out_box : Widget {
  Out_box(Point xy, int w, int h, const std::string& s)
      : Widget { xy, w, h, s, 0 }
  {
  }
  void put(int);
  void put(const std::string&);
  void attach(Window& win) override;
};

} // namespace Graph_lib

#endif

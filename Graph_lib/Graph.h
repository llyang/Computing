#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

#include "Point.h"

#include "fltk.h"

namespace Graph_lib {

// Supporting classes for colors, line styles and fonts

class Color {
public:
  enum Color_type {
    red = FL_RED,
    blue = FL_BLUE,
    green = FL_GREEN,
    yellow = FL_YELLOW,
    white = FL_WHITE,
    black = FL_BLACK,
    magenta = FL_MAGENTA,
    cyan = FL_CYAN,
    dark_red = FL_DARK_RED,
    dark_green = FL_DARK_GREEN,
    dark_yellow = FL_DARK_YELLOW,
    dark_blue = FL_DARK_BLUE,
    dark_magenta = FL_DARK_MAGENTA,
    dark_cyan = FL_DARK_CYAN
  };
  enum Transparency { invisible = 0,
    visible = 255 };

  explicit Color(Color_type cc)
      : c { static_cast<Fl_Color>(cc) }
      , v { visible }
  {
  }
  Color(Color_type cc, Transparency vv)
      : c { static_cast<Fl_Color>(cc) }
      , v { vv }
  {
  }
  explicit Color(int cc)
      : c { static_cast<Fl_Color>(cc) }
      , v { visible }
  {
  }
  explicit Color(Transparency vv)
      : c { Fl_Color {} }
      , v { vv }
  {
  }

  int as_int() const { return c; }
  char visibility() const { return v; }
  void set_visibility(Transparency vv) { v = vv; }

private:
  Fl_Color c;
  int v;
};

class Line_style {
public:
  enum Line_style_type {
    solid = FL_SOLID, // -------
    dash = FL_DASH, // - - - -
    dot = FL_DOT, // .......
    dashdot = FL_DASHDOT, // - . - .
    dashdotdot = FL_DASHDOTDOT, // -..-..
  };

  explicit Line_style(Line_style_type ss)
      : s { ss }
      , w { 0 }
  {
  }
  Line_style(Line_style_type lst, int ww)
      : s { lst }
      , w { ww }
  {
  }
  explicit Line_style(int ss)
      : s { ss }
      , w { 0 }
  {
  }

  int width() const { return w; }
  int style() const { return s; }

private:
  int s;
  int w;
};

class Font {
public:
  enum Font_type {
    helvetica = FL_HELVETICA,
    helvetica_bold = FL_HELVETICA_BOLD,
    helvetica_italic = FL_HELVETICA_ITALIC,
    helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
    courier = FL_COURIER,
    courier_bold = FL_COURIER_BOLD,
    courier_italic = FL_COURIER_ITALIC,
    courier_bold_italic = FL_COURIER_BOLD_ITALIC,
    times = FL_TIMES,
    times_bold = FL_TIMES_BOLD,
    times_italic = FL_TIMES_ITALIC,
    times_bold_italic = FL_TIMES_BOLD_ITALIC,
    symbol = FL_SYMBOL,
    screen = FL_SCREEN,
    screen_bold = FL_SCREEN_BOLD,
    zapf_dingbats = FL_ZAPF_DINGBATS
  };

  explicit Font(Font_type ff)
      : f { ff }
  {
  }
  explicit Font(int ff)
      : f { ff }
  {
  }

  int as_int() const { return f; }

private:
  int f;
};

class Fill {
public:
  Fill()
      : no_fill { true }
      , fcolor { 0 }
  {
  }
  explicit Fill(Color c)
      : no_fill { false }
      , fcolor { c }
  {
  }

  void set_fill_color(Color col) { fcolor = col; }
  Color fill_color() { return fcolor; }

protected:
  bool no_fill;
  Color fcolor;
};

////////////////////////////////////////

// Base class for all shapes

class Shape { // deals with color and style, and holds sequence of lines
public:
  void draw() const; // deal with color and draw_lines

  virtual void move(int dx, int dy); // move the shape +=dx and +=dy

  void set_color(Color col) { lcolor = col; }
  Color color() const { return lcolor; }

  void set_style(Line_style sty) { ls = sty; }
  Line_style style() const { return ls; }

  void set_fill_color(Color col) { fcolor = col; }
  Color fill_color() const { return fcolor; }

  Point point(int i) const { return points[i]; }
  int number_of_points() const { return int(points.size()); }

  virtual ~Shape() {}
  Shape(const Shape&) = delete;
  Shape& operator=(const Shape&) = delete;

protected:
  Shape() {}
  explicit Shape(std::initializer_list<Point> lst); // add() the Points to this Shape

  void add(Point p) { points.push_back(p); }
  void set_point(int i, Point p) { points[i] = p; }

  virtual void draw_lines() const; // simply draw the appropriate lines

private:
  std::vector<Point> points; // not used by all shapes
  Color lcolor { static_cast<int>(fl_color()) };
  Line_style ls { 0 };
  Color fcolor { Color::invisible };
};

////////////////////////////////////////

// Simple shapes

struct Line : Shape {
  Line(Point p1, Point p2)
  {
    add(p1);
    add(p2);
  }
};

class Rectangle : public Shape {
public:
  Rectangle(Point xy, int ww, int hh)
      : w { ww }
      , h { hh }
  {
    if (h <= 0 || w <= 0) {
      throw std::runtime_error { "Bad rectangle: non-positive side" };
    }
    add(xy);
  }

  Rectangle(Point x, Point y)
      : w { y.x - x.x }
      , h { y.y - x.y }
  {
    if (h <= 0 || w <= 0) {
      throw std::runtime_error { "Bad rectangle: first point is not top left" };
    }
    add(x);
  }

  void draw_lines() const override;

  int height() const { return h; }
  int width() const { return w; }

private:
  int w; // width
  int h; // height
};

struct Open_polyline : Shape { // open sequence of lines
  using Shape::Shape;
  void add(Point p) { Shape::add(p); }
  void draw_lines() const override;
};

struct Closed_polyline : Open_polyline { // closed sequence of lines
  using Open_polyline::Open_polyline;
  void draw_lines() const override;
};

struct Lines : Shape { // indepentdent lines
  Lines() {}

  explicit Lines(std::initializer_list<Point> lst)
      : Shape { lst }
  {
    if (lst.size() % 2) {
      throw std::runtime_error { "odd number of points for Lines" };
    }
  }

  void draw_lines() const override;
  void add(Point p1, Point p2)
  {
    Shape::add(p1);
    Shape::add(p2);
  }
};

////////////////////////////////////////

class Text : public Shape {
public:
  // the point is the bottom left of the first letter
  Text(Point x, const std::string& s)
      : lab { s }
  {
    add(x);
  }

  void draw_lines() const override;

  void set_label(const std::string& s) { lab = s; }
  std::string label() const { return lab; }

  void set_font(Font f) { fnt = f; }
  Font font() const { return Font(fnt); }

  void set_font_size(int s) { fnt_sz = s; }
  int font_size() const { return fnt_sz; }

private:
  std::string lab; // label
  Font fnt { fl_font() };
  int fnt_sz { (14 < fl_size()) ? fl_size() : 14 }; // at least 14 point
};

////////////////////////////////////////

class Circle : public Shape {
public:
  // center and radius
  Circle(Point p, int rr)
      : r { rr }
  {
    add(Point { p.x - r, p.y - r });
  }

  void draw_lines() const override;

  Point center() const { return { point(0).x + r, point(0).y + r }; }

  void set_radius(int rr) { r = rr; }
  int radius() const { return r; }

private:
  int r;
};

class Ellipse : public Shape {
public:
  // center, min, and max distance from center
  Ellipse(Point p, int ww, int hh)
      : w { ww }
      , h { hh }
  {
    add(Point { p.x - ww, p.y - hh });
  }

  void draw_lines() const override;

  Point center() const { return { point(0).x + w, point(0).y + h }; }
  Point focus1() const
  {
    return { center().x + int(std::sqrt(double(w * w - h * h))), center().y };
  }
  Point focus2() const
  {
    return { center().x - int(std::sqrt(double(w * w - h * h))), center().y };
  }

  void set_major(int ww) { w = ww; }
  int get_major() const { return w; }
  void set_minor(int hh) { h = hh; }
  int get_minor() const { return h; }

private:
  int w;
  int h;
};

////////////////////////////////////////

class Marked_polyline : public Open_polyline {
public:
  explicit Marked_polyline(const std::string& m)
      : mark { m }
  {
  }
  void draw_lines() const override;

private:
  std::string mark;
};

struct Marks : Marked_polyline {
  explicit Marks(const std::string& m)
      : Marked_polyline { m }
  {
    set_color(Color { Color::invisible });
  }
};

struct Mark : Marks {
  Mark(Point xy, char c)
      : Marks { std::string(1, c) }
  {
    add(xy);
  }
};

////////////////////////////////////////

// Image files

struct Bad_image : Fl_Image {
  Bad_image(int h, int w)
      : Fl_Image { h, w, 0 }
  {
  }
  void draw(int x, int y, int, int, int, int) { draw_empty(x, y); }
};

struct Suffix {
  enum Encoding { none,
    jpg,
    gif,
    png,
    bmp };
};

Suffix::Encoding get_encoding(const std::string& s);

class Image : public Shape {
public:
  Image(Point xy, std::string s, Suffix::Encoding e = Suffix::none);
  ~Image()
  {
    if (p)
      delete p;
  }

  void draw_lines() const override;

  void set_mask(Point xy, int ww, int hh)
  {
    w = ww;
    h = hh;
    cx = xy.x;
    cy = xy.y;
  }

  void move(int dx, int dy) override
  {
    Shape::move(dx, dy);
    p->draw(point(0).x, point(0).y);
  }

private:
  int w, h, cx, cy; // define "masking box" within image relative to position (cx,cy)
  Text fn;
  Fl_Image* p;
};

////////////////////////////////////////

// Polygon is a special version of Closed_polyline:
// lines should not intersect!
struct Polygon : Closed_polyline {
  using Closed_polyline::Closed_polyline;
  void add(Point p);
  void draw_lines() const override;
};

} // namespace Graph_lib

#endif


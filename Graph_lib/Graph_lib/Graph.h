#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

#include "Point.h"

#include "fltk.h"

namespace Graph_lib {

// Supporting classes for colors, line styles and fonts

// a wrapper for Fl_Color
enum class Color {
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

// a wrapper for line styles in FLTK
enum class Stroke {
  solid = FL_SOLID, // -------
  dash = FL_DASH, // - - - -
  dot = FL_DOT, // .......
  dashdot = FL_DASHDOT, // - . - .
  dashdotdot = FL_DASHDOTDOT, // -..-..
};

// a wrapper for Fl_Font
enum class Font {
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

class Line_style {
public:
  explicit Line_style(int width = 1, Color c = Color::black, Stroke s = Stroke::solid, bool visible = true);

  int width() const { return width_; }
  void set_width(int w) { width_ = w; }

  Color color() const { return color_; }
  void set_color(Color c) { color_ = c; }

  Stroke stroke() const { return stroke_; }
  void set_stroke(Stroke s) { stroke_ = s; }

  bool visibility() const { return visible_; }
  void set_visibility(bool v) { visible_ = v; }

private:
  int width_;
  Color color_;
  Stroke stroke_;
  bool visible_;
};

class Fill_style {
public:
  explicit Fill_style(Color c = Color::black, bool visible = false);

  Color color() const { return color_; }
  void set_color(Color c) { color_ = c; }

  bool visibility() const { return visible_; }
  void set_visibility(bool v) { visible_ = v; }

private:
  Color color_;
  bool visible_;
};

class Text_style {
public:
  explicit Text_style(int size = 14, Color c = Color::black, Font f = Font::helvetica);

  int size() const { return size_; }
  void set_size(int size) { size_ = size; }

  Color color() const { return color_; }
  void set_color(Color c) { color_ = c; }

  Font font() const { return font_; }
  void set_font(Font f) { font_ = f; }

private:
  int size_;
  Color color_;
  Font font_;
};
////////////////////////////////////////

// Base class for all shapes

class Shape { // deals with color and style, and holds sequence of lines
public:
  void draw() const; // deal with color and draw_lines

  virtual void move(int dx, int dy); // move the shape +=dx and +=dy

  // These two need to be virtual since class Text needs to override them
  virtual Color color() const { return line_color(); }
  virtual void set_color(Color c) { set_line_color(c); }

  Line_style line_style() const { return line_style_; }
  int line_width() const { return line_style_.width(); }
  Color line_color() const { return line_style_.color(); }
  Stroke line_stroke() const { return line_style_.stroke(); }

  // These two need to be virtual since class Marks needs to override them
  virtual void set_line_style(Line_style sty) { line_style_ = sty; }
  virtual void set_line_visibility(bool v) { line_style_.set_visibility(v); }
  void set_line_width(int w) { line_style_.set_width(w); }
  void set_line_color(Color c) { line_style_.set_color(c); }
  void set_line_stroke(Stroke s) { line_style_.set_stroke(s); }

  Fill_style fill_style() const { return fill_style_; }
  Color fill_color() const { return fill_style_.color(); }

  // These three need to be virtual since class Marks needs to override them
  virtual void set_fill_style(Fill_style sty) { fill_style_ = sty; }
  virtual void set_fill_color(Color color) { fill_style_ = Fill_style { color, true }; }
  virtual void set_fill_visibility(bool v) { fill_style_.set_visibility(v); }

  Point point(size_t i) const { return points[i]; }
  size_t number_of_points() const { return points.size(); }

  virtual ~Shape() = default;

  Shape(const Shape&) = delete;
  Shape& operator=(const Shape&) = delete;

protected:
  Shape() = default;

  Shape(std::initializer_list<Point> lst); // add the Points to this Shape

  virtual void draw_lines() const; // simply draw the appropriate lines

  std::vector<Point> points; // not used by all shapes

private:
  Line_style line_style_;
  Fill_style fill_style_;
};

////////////////////////////////////////

// Simple shapes

struct Line : Shape {
  Line(Point p1, Point p2);
};

class Lines : public Shape { // independent lines
public:
  Lines()
      : Shape {}
  {
  }
  Lines(std::initializer_list<Point> lst);

  void add(Point p1, Point p2);

protected:
  void draw_lines() const override;
};

class Rectangle : public Shape {
public:
  Rectangle(Point xy, int ww, int hh);

  Rectangle(Point x, Point y);

  int width() const { return w; }
  int height() const { return h; }

protected:
  void draw_lines() const override;

private:
  int w; // width
  int h; // height
};

class Open_polyline : public Shape { // open sequence of lines
public:
  Open_polyline()
      : Shape()
  {
  }

  Open_polyline(std::initializer_list<Point> lst)
      : Shape { lst }
  {
  }

  // this needs to be virtual since Polygon needs to override it
  virtual void add(Point p) { points.push_back(p); }

protected:
  void draw_lines() const override;
};

class Closed_polyline : public Open_polyline { // closed sequence of lines
public:
  using Open_polyline::Open_polyline;

protected:
  void draw_lines() const override;
};

////////////////////////////////////////

class Marked_polyline : public Open_polyline {
public:
  explicit Marked_polyline(std::string m)
      : mark { std::move(m) }
  {
  }

protected:
  void draw_lines() const override;

private:
  std::string mark;
};

class Marks : public Marked_polyline {
public:
  explicit Marks(std::string m)
      : Marked_polyline { std::move(m) }
  {
    Shape::set_line_visibility(false);
  }

protected:
  void set_line_style(Line_style) override {};
  void set_line_visibility(bool) override {};
  void set_fill_style(Fill_style) override {};
  void set_fill_color(Color) override {};
  void set_fill_visibility(bool) override {};
};

class Mark : public Marks {
public:
  Mark(Point xy, char c);

private:
  void add(Point) override {};
};

////////////////////////////////////////

class Circle : public Shape {
public:
  // center and radius
  Circle(Point p, int rr);

  Point center() const { return { point(0).x + r, point(0).y + r }; }

  void set_radius(int rr) { r = rr; }
  int radius() const { return r; }

protected:
  void draw_lines() const override;

private:
  int r;
};

class Ellipse : public Shape {
public:
  // center, min, and max distance from center
  Ellipse(Point p, int ww, int hh);

  Point center() const { return { point(0).x + w, point(0).y + h }; }
  Point focus1() const { return { center().x + int(std::sqrt(w * w - h * h)), center().y }; }
  Point focus2() const { return { center().x - int(std::sqrt(w * w - h * h)), center().y }; }

  void set_major(int ww) { w = ww; }
  int get_major() const { return w; }
  void set_minor(int hh) { h = hh; }
  int get_minor() const { return h; }

protected:
  void draw_lines() const override;

private:
  int w;
  int h;
};

////////////////////////////////////////

class Text : public Shape {
public:
  // the point is the bottom left of the first letter
  Text(Point x, std::string s)
      : label_ { std::move(s) }
  {
    points.push_back(x);
  }

  void set_label(std::string s) { label_ = std::move(s); }
  std::string label() const { return label_; }

  void set_text_style(Text_style text_style) { text_style_ = text_style; }
  Text_style text_style() const { return text_style_; }

  void set_color(Color c) override { text_style_.set_color(c); }
  Color color() const override { return text_style_.color(); }

  void set_font(Font f) { text_style_.set_font(f); }
  Font font() const { return text_style_.font(); }

  void set_font_size(int sz) { text_style_.set_size(sz); }
  int font_size() const { return text_style_.size(); }

protected:
  void draw_lines() const override;

private:
  std::string label_; // label
  Text_style text_style_;
};

////////////////////////////////////////

// Image files

struct Bad_image : Fl_Image {
  Bad_image(int w, int h)
      : Fl_Image { w, h, 0 }
  {
  }
  void draw(int x, int y, int, int, int, int) override { draw_empty(x, y); }
};

enum class Encoding {
  none,
  jpg,
  gif,
  png,
  bmp
};

Encoding get_encoding(const std::string& s);

class Image : public Shape {
public:
  Image(Point xy, const std::string& s, Encoding e = Encoding::none);
  ~Image() override { delete p; }

  void draw_lines() const override;

  void set_mask(Point xy, int ww, int hh);

  void move(int dx, int dy) override;

private:
  int w, h, cx, cy; // define "masking box" within image relative to position (cx,cy)
  Text error_text;
  Fl_Image* p;
};

////////////////////////////////////////

// Polygon is a special version of Closed_polyline:
// lines should not intersect!
class Polygon : public Closed_polyline {
public:
  using Closed_polyline::Closed_polyline;
  void add(Point p) override;

protected:
  void draw_lines() const override;
};

} // namespace Graph_lib

#endif

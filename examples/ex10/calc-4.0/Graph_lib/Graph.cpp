#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

#include "Graph.h"

using std::runtime_error;
using std::string;

namespace Graph_lib {

Line_style::Line_style(int width, Color c, Stroke s, bool visible)
    : width_ { width }
    , color_ { c }
    , stroke_ { s }
    , visible_ { visible }
{
}

Fill_style::Fill_style(Color c, bool visible)
    : color_ { c }
    , visible_ { visible }
{
}

Text_style::Text_style(int size, Color c, Font font)
    : size_ { size }
    , color_ { c }
    , font_ { font }
{
}

////////////////////////////////////////

Shape::Shape(std::initializer_list<Point> lst)
{
  for (const auto& p : lst) {
    points.push_back(p);
  }
}

void Shape::draw() const
{
  // this will change the color and line style for later drawings
  fl_color(static_cast<Fl_Color>(line_style().color()));
  fl_line_style(static_cast<int>(line_style().stroke()), line_style().width());
  draw_lines();
}

void Shape::draw_lines() const
{
  if (line_style().visibility() && points.size() > 1) {
    for (size_t i = 1; i < points.size(); ++i)
      fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
  }
}

void Shape::move(int dx, int dy)
{
  for (auto& p : points) {
    p.x += dx;
    p.y += dy;
  }
}

////////////////////////////////////////

Line::Line(Point p1, Point p2)
{
  points.push_back(p1);
  points.push_back(p2);
}

Lines::Lines(std::initializer_list<Point> lst)
    : Shape { lst }
{
  if (lst.size() % 2 != 0) {
    throw runtime_error { "odd number of points for Lines" };
  }
}

void Lines::draw_lines() const
{
  if (line_style().visibility())
    for (size_t i = 1; i < number_of_points(); i += 2)
      fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
}

void Lines::add(Point p1, Point p2)
{
  points.push_back(p1);
  points.push_back(p2);
}

////////////////////////////////////////

Rectangle::Rectangle(Point xy, int ww, int hh)
    : w { ww }
    , h { hh }
{
  if (h <= 0 || w <= 0) {
    throw runtime_error { "Bad rectangle: non-positive side" };
  }
  points.push_back(xy);
}

Rectangle::Rectangle(Point x, Point y)
    : w { y.x - x.x }
    , h { y.y - x.y }
{
  if (h <= 0 || w <= 0) {
    throw runtime_error { "Bad rectangle: first point is not top left" };
  }
  points.push_back(x);
}

void Rectangle::draw_lines() const
{
  if (fill_style().visibility()) { // fill
    fl_color(static_cast<Fl_Color>(fill_style().color()));
    fl_rectf(point(0).x, point(0).y, w, h);
    fl_color(static_cast<Fl_Color>(line_style().color()));
  }

  if (line_style().visibility()) { // edge on top of fill
    fl_rect(point(0).x, point(0).y, w, h);
  }
}

////////////////////////////////////////

void Open_polyline::draw_lines() const
{
  if (fill_style().visibility()) {
    fl_color(static_cast<Fl_Color>(fill_style().color()));
    fl_begin_complex_polygon();
    for (size_t i = 0; i < number_of_points(); ++i) {
      fl_vertex(point(i).x, point(i).y);
    }
    fl_end_complex_polygon();
    fl_color(static_cast<Fl_Color>(line_style().color()));
  }

  if (line_style().visibility()) {
    Shape::draw_lines();
  }
}

void Closed_polyline::draw_lines() const
{
  Open_polyline::draw_lines();
  if (line_style().visibility()) { // draw closing line:
    fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
  }
}

////////////////////////////////////////

void draw_mark(Point xy, char c)
{
  constexpr int dx { 4 };
  constexpr int dy { 4 };
  string m(1, c);
  fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
}

void Marked_polyline::draw_lines() const
{
  Open_polyline::draw_lines();
  for (size_t i = 0; i < number_of_points(); ++i)
    draw_mark(point(i), mark[i % mark.size()]);
}

Mark::Mark(Point xy, char c)
    : Marks { string(1, c) }
{
  points.push_back(xy);
}

////////////////////////////////////////

Circle::Circle(Point p, int rr)
    : r { rr }
{
  points.push_back(Point { p.x - r, p.y - r });
}

void Circle::draw_lines() const
{
  if (fill_style().visibility()) { // fill
    fl_color(static_cast<Fl_Color>(fill_style().color()));
    fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
    fl_color(static_cast<Fl_Color>(line_style().color()));
  }

  if (line_style().visibility()) {
    fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
  }
}

Ellipse::Ellipse(Point p, int ww, int hh)
    : w { ww }
    , h { hh }
{
  points.push_back(Point { p.x - ww, p.y - hh });
}

void Ellipse::draw_lines() const
{
  if (fill_style().visibility()) { // fill
    fl_color(static_cast<Fl_Color>(fill_style().color()));
    fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, 0, 360);
    fl_color(static_cast<Fl_Color>(line_style().color()));
  }

  if (line_style().visibility()) {
    fl_arc(point(0).x, point(0).y, w + w, h + h, 0, 360);
  }
}

////////////////////////////////////////

void Text::draw_lines() const
{
  fl_color(static_cast<Fl_Color>(text_style().color()));
  fl_font(static_cast<Fl_Font>(text_style().font()), text_style().size());
  fl_draw(label_.c_str(), point(0).x, point(0).y);
}

////////////////////////////////////////

// Image files

const std::map<string, Encoding>& init_suffix_map()
{
  static std::map<string, Encoding> suffix_map;
  suffix_map["jpg"] = Encoding::jpg;
  suffix_map["JPG"] = Encoding::jpg;
  suffix_map["jpeg"] = Encoding::jpg;
  suffix_map["JPEG"] = Encoding::jpg;
  suffix_map["gif"] = Encoding::gif;
  suffix_map["GIF"] = Encoding::gif;
  suffix_map["bmp"] = Encoding::bmp;
  suffix_map["BMP"] = Encoding::bmp;
  suffix_map["png"] = Encoding::png;
  suffix_map["PNG"] = Encoding::png;
  return suffix_map;
}

Encoding get_encoding(const string& s)
// try to deduce type from file name using a lookup table
{
  auto suffix_map { init_suffix_map() };

  auto p { find(s.begin(), s.end(), '.') };
  if (p == s.end())
    return Encoding::none; // no suffix

  string suf { p + 1, s.end() };
  return suffix_map[suf];
}

bool can_open(const string& s)
// check if a file named s exists and can be opened for reading
{
  std::ifstream ff { s.c_str() };
  return static_cast<bool>(ff);
}

// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, const string& s, Encoding e)
    : w { 0 }
    , h { 0 }
    , error_text { xy, "" }
    , p { nullptr }
{

  points.push_back(xy);

  if (!can_open(s)) {
    error_text.set_label("cannot open \"" + s + '\"');
    p = new Bad_image { 30, 20 }; // the "error image"
    return;
  }

  if (e == Encoding::none)
    e = get_encoding(s);

  switch (e) {
  case Encoding::jpg:
    p = new Fl_JPEG_Image { s.c_str() };
    break;
  case Encoding::gif:
    p = new Fl_GIF_Image { s.c_str() };
    break;
  case Encoding::png:
    p = new Fl_PNG_Image { s.c_str() };
    break;
  case Encoding::bmp:
    p = new Fl_BMP_Image { s.c_str() };
    break;
  default: // Unsupported image encoding
    error_text.set_label("unsupported file type \"" + s + '\"');
    p = new Bad_image { 30, 20 }; // the "error image"
  }
}

void Image::move(int dx, int dy)
{
  Shape::move(dx, dy);
  p->draw(point(0).x, point(0).y);
}

void Image::set_mask(Point xy, int ww, int hh)
{
  w = ww;
  h = hh;
  cx = xy.x;
  cy = xy.y;
}

void Image::draw_lines() const
{
  if (!error_text.label().empty())
    error_text.draw();

  if (w > 0 && h > 0)
    p->draw(point(0).x, point(0).y, w, h, cx, cy);
  else
    p->draw(point(0).x, point(0).y);
}

////////////////////////////////////////

// Polygon related functions

// does two lines (p1,p2) and (p3,p4) intersect?
// if so return the length of (p1->intersection point)
// in unit of the length of (p1->p2)
double line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
  int x1 { p1.x };
  int x2 { p2.x };
  int x3 { p3.x };
  int x4 { p4.x };
  int y1 { p1.y };
  int y2 { p2.y };
  int y3 { p3.y };
  int y4 { p4.y };

  // denominator
  int d { (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1) };
  if (d == 0) {
    parallel = true;
    return 0;
  }
  parallel = false;
  return ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / static_cast<double>(d);
}

// intersection between two line segments
// returns true if the two segments intersect,
// in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection)
{
  bool parallel;
  double u { line_intersect(p1, p2, p3, p4, parallel) };
  if (parallel || u < 0 || u > 1)
    return false;
  intersection.x = static_cast<int>(p1.x + u * (p2.x - p1.x));
  intersection.y = static_cast<int>(p1.y + u * (p2.y - p1.y));
  return true;
}

void Polygon::add(Point p)
{
  size_t np { number_of_points() };

  if (np > 1) { // check that the new line isn't parallel to the previous one
    if (p == point(np - 1)) {
      throw runtime_error { "polygon point equal to previous point" };
    }
    bool parallel;
    line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
    if (parallel) {
      throw runtime_error { "two polygon points lie in a straight line" };
    }

    for (size_t i = 1; i < np - 1; ++i) {
      // check that new segment doesn't intersect an old one
      Point ignore(0, 0);
      if (line_segment_intersect(point(np - 1), p, point(i - 1), point(i), ignore)) {
        throw runtime_error { "intersection in polygon" };
      }
    }
  }

  Closed_polyline::add(p);
}

void Polygon::draw_lines() const
{
  if (number_of_points() < 3) {
    throw runtime_error { "less than 3 points in a Polygon" };
  }
  Closed_polyline::draw_lines();
}

} // namespace Graph_lib

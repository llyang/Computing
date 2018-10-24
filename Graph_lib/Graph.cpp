#include <algorithm>
#include <fstream>
#include <map>

#include "Graph.h"

using std::string;
using std::ifstream;
using std::runtime_error;

namespace Graph_lib {

////////////////////////////////////////

void Shape::draw_lines() const {
  if (color().visibility() && 1 < points.size()) // draw sole pixel?
    for (unsigned int i = 1; i < points.size(); ++i)
      fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
}

void Shape::draw() const {
  Fl_Color oldc = fl_color();
  // there is no good portable way of retrieving the current style
  fl_color(lcolor.as_int());
  fl_line_style(ls.style(), ls.width());
  draw_lines();
  fl_color(oldc); // reset color (to pevious) and style (to default)
  fl_line_style(0);
}

void Shape::move(int dx, int dy) {
  for (unsigned int i = 0; i < points.size(); ++i) {
    points[i].x += dx;
    points[i].y += dy;
  }
}

////////////////////////////////////////

void Open_polyline::draw_lines() const {
  if (fill_color().visibility()) {
    fl_color(fill_color().as_int());
    fl_begin_complex_polygon();
    for (int i = 0; i < number_of_points(); ++i) {
      fl_vertex(point(i).x, point(i).y);
    }
    fl_end_complex_polygon();
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility())
    Shape::draw_lines();
}

void Closed_polyline::draw_lines() const {

  Open_polyline::draw_lines();

  if (color().visibility()) // draw closing line:
    fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y,
            point(0).x, point(0).y);
}

void Lines::draw_lines() const {
  if (color().visibility())
    for (int i = 1; i < number_of_points(); i += 2)
      fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
}

void Rectangle::draw_lines() const {
  if (fill_color().visibility()) { // fill
    fl_color(fill_color().as_int());
    fl_rectf(point(0).x, point(0).y, w, h);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) { // edge on top of fill
    fl_color(color().as_int());
    fl_rect(point(0).x, point(0).y, w, h);
  }
}

void Circle::draw_lines() const {
  if (fill_color().visibility()) { // fill
    fl_color(fill_color().as_int());
    fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
  }
}

void Ellipse::draw_lines() const {
  if (fill_color().visibility()) { // fill
    fl_color(fill_color().as_int());
    fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, 0, 360);
    fl_color(color().as_int()); // reset color
  }

  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x, point(0).y, w + w, h + h, 0, 360);
  }
}

////////////////////////////////////////

void Text::draw_lines() const {
  int ofnt = fl_font();
  int osz = fl_size();
  fl_font(fnt.as_int(), fnt_sz);
  fl_draw(lab.c_str(), point(0).x, point(0).y);
  fl_font(ofnt, osz);
}

////////////////////////////////////////

void draw_mark(Point xy, char c) {
  constexpr int dx{4};
  constexpr int dy{4};
  string m(1, c);
  fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
}

void Marked_polyline::draw_lines() const {
  Open_polyline::draw_lines();
  for (int i = 0; i < number_of_points(); ++i)
    draw_mark(point(i), mark[i % mark.size()]);
}

////////////////////////////////////////

// Image files

std::map<string, Suffix::Encoding> suffix_map;

int init_suffix_map() {
  suffix_map["jpg"] = Suffix::jpg;
  suffix_map["JPG"] = Suffix::jpg;
  suffix_map["jpeg"] = Suffix::jpg;
  suffix_map["JPEG"] = Suffix::jpg;
  suffix_map["gif"] = Suffix::gif;
  suffix_map["GIF"] = Suffix::gif;
  suffix_map["bmp"] = Suffix::bmp;
  suffix_map["BMP"] = Suffix::bmp;
  suffix_map["png"] = Suffix::png;
  suffix_map["PNG"] = Suffix::png;
  return 0;
}

Suffix::Encoding get_encoding(const string &s)
// try to deduce type from file name using a lookup table
{
  static int x{init_suffix_map()};

  string::const_iterator p = find(s.begin(), s.end(), '.');
  if (p == s.end())
    return Suffix::none; // no suffix

  string suf{p + 1, s.end()};
  return suffix_map[suf];
}

bool can_open(const string &s)
// check if a file named s exists and can be opened for reading
{
  ifstream ff{s.c_str()};
  return static_cast<bool>(ff);
}

// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, string s, Suffix::Encoding e) : w{0}, h{0}, fn{xy, ""} {

  add(xy);

  if (!can_open(s)) {
    fn.set_label("cannot open \"" + s + '\"');
    p = new Bad_image{30, 20}; // the "error image"
    return;
  }

  if (e == Suffix::none)
    e = get_encoding(s);

  switch (e) {
  case Suffix::jpg:
    p = new Fl_JPEG_Image{s.c_str()};
    break;
  case Suffix::gif:
    p = new Fl_GIF_Image{s.c_str()};
    break;
  case Suffix::png:
    p = new Fl_PNG_Image{s.c_str()};
    break;
  case Suffix::bmp:
    p = new Fl_BMP_Image{s.c_str()};
    break;
  default: // Unsupported image encoding
    fn.set_label("unsupported file type \"" + s + '\"');
    p = new Bad_image{30, 20}; // the "error image"
  }
}

void Image::draw_lines() const {
  if (fn.label() != "")
    fn.draw_lines();

  if (w && h)
    p->draw(point(0).x, point(0).y, w, h, cx, cy);
  else
    p->draw(point(0).x, point(0).y);
}

////////////////////////////////////////

// Polygon related functions

// does two lines (p1,p2) and (p3,p4) intersect?
// if so return the length of (p1->intersection point)
// in unit of the length of (p1->p2)
inline double line_intersect(Point p1, Point p2, Point p3, Point p4,
                             bool &parallel) {
  double x1 = p1.x;
  double x2 = p2.x;
  double x3 = p3.x;
  double x4 = p4.x;
  double y1 = p1.y;
  double y2 = p2.y;
  double y3 = p3.y;
  double y4 = p4.y;

  double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
  if (denom == 0) {
    parallel = true;
    return 0;
  }
  parallel = false;
  return ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
}

// intersection between two line segments
// returns true if the two segments intersect,
// in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4,
                            Point &intersection) {
  bool parallel;
  double u = line_intersect(p1, p2, p3, p4, parallel);
  if (parallel || u < 0 || u > 1)
    return false;
  intersection.x = p1.x + u * (p2.x - p1.x);
  intersection.y = p1.y + u * (p2.y - p1.y);
  return true;
}

void Polygon::add(Point p) {
  int np = number_of_points();

  if (1 < np) { // check that the new line isn't parallel to the previous one
    if (p == point(np - 1)) {
      throw runtime_error{"polygon point equal to previous point"};
    }
    bool parallel;
    line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
    if (parallel) {
      throw runtime_error{"two polygon points lie in a straight line"};
    }
  }

  for (int i = 1; i < np - 1; ++i) {
    // check that new segment doesn't interset an old one
    Point ignore(0, 0);
    if (line_segment_intersect(point(np - 1), p, point(i - 1), point(i),
                               ignore)) {
      throw runtime_error{"intersection in polygon"};
    }
  }

  Closed_polyline::add(p);
}

void Polygon::draw_lines() const {
  if (number_of_points() < 3) {
    throw runtime_error{"less than 3 points in a Polygon"};
  }
  Closed_polyline::draw_lines();
}

} // namespace Graph_lib


#ifndef POINT_GUARD
#define POINT_GUARD

namespace Graph_lib {

struct Point {
  int x, y;
  Point(int xx, int yy) : x{xx}, y{yy} {}
};

inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

inline bool operator!=(Point a, Point b) { return !(a == b); }

} // namespace Graph_lib

#endif


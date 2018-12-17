#include <iostream>

#include "List.h"
#include "Vector.h"

using std::cout;

double* Vector_high(double* b, double* e)
// just for demonstration, no error detection!
// would fail if b==nullptr || e==nullptr || e<b
{
  double* high { b };
  for (double* p = b; p != e; ++p) {
    if (*p > *high)
      high = p;
  }
  return high;
}

Link* List_high(Link* b, Link* e)
// e must be nullptr, b must not be nullptr!
{
  Link* high { b };
  for (Link* p = b; p != e; p = p->succ) {
    if (p->val > high->val)
      high = p;
  }
  return high;
}

int main()
{
  double a[5] { 2.3, 4.5, 8.9, 0.6, 7.4 };
  double* ha { Vector_high(a, a + 5) };
  if (ha)
    cout << *ha << '\n';

  Vector b { 2.3, 4.5, 8.9, 0.6, 7.4 };
  double* hb { Vector_high(&b[0], &b[0] + b.size()) };
  if (hb)
    cout << *hb << '\n';

  List c { 2.3, 4.5, 8.9, 0.6, 7.4 };
  Link* hc { List_high(c.begin(), c.end()) };
  if (hc)
    cout << hc->val << '\n';
}

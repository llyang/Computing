#include <iostream>

#include "List.h"
#include "Vector.h"

using std::cout;

template <typename Iter>
Iter high(Iter b, Iter e)
{
  Iter high { b };
  for (auto p = b; p != e; ++p) {
    if (*p > *high)
      high = p;
  }
  return high;
}

int main()
{
  double a[5] { 2.3, 4.5, 8.9, 0.6, 7.4 };
  auto ha { high(a, a + 5) };
  if (ha)
    cout << *ha << '\n';

  Vector b { 2.3, 4.5, 8.9, 0.6, 7.4 };
  auto hb { high(b.begin(), b.end()) };
  cout << *hb << '\n';

  List c { 12.3, 14.5, 18.9, 10.6, 17.4 };
  auto hc { high(c.begin(), c.end()) };
  cout << *hc << '\n';

  cout << '\n';

  for (auto x : b)
    cout << x << ' ';
  cout << '\n';

  for (auto x : c)
    cout << x << ' ';
  cout << '\n';
}

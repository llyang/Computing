#include <iostream>

#include "Vector.h"

using std::cin;
using std::cout;

Vector f1(double x)
{
  Vector v { x, x + 1, x + 2 };
  return v;
}

Vector f2(double x)
{
  Vector v1 { x, x + 1, x + 2 };
  Vector v2 { x, x - 1, x - 2 };
  if (x > 0) {
    return v1;
  } else {
    return v2;
  }
}

int main()
{
  cout << "Please input a number: ";
  double n;
  cin >> n;

  Vector v { 1, 2, 3 };
  cout << "v.size() = " << v.size() << '\n';
  cout << "v[0] = " << v[0] << "\n\n";

  Vector v1 { f1(n) };
  cout << "v1.size() = " << v1.size() << '\n';
  cout << "v1[0] = " << v1[0] << "\n\n";

  Vector v2 { f2(n) };
  cout << "v2.size() = " << v2.size() << '\n';
  cout << "v2[0] = " << v2[0] << "\n\n";
}

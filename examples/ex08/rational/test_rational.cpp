#include <algorithm>
#include <iostream>
#include <vector>

#include "Rational.h"

using std::cerr;
using std::cin;
using std::cout;
using std::vector;

void test1()
{
  cout << "Please input two rational numbers: ";

  Calc::Rational r1;
  Calc::Rational r2;
  cin >> r1 >> r2;
  if (!cin) {
    cerr << "wrong inputs\n";
    return;
  }

  cout << "r1 == " << r1 << '\n';
  cout << "r2 == " << r2 << '\n';

  cout << "+r1 == " << +r1 << '\n';
  cout << "-r1 == " << -r1 << '\n';
  cout << "r1+r2 == " << r1 + r2 << '\n';
  cout << "r1-r2 == " << r1 - r2 << '\n';
  cout << "r1*r2 == " << r1 * r2 << '\n';
  cout << "r1/r2 == " << r1 / r2 << '\n';
  cout << "2+r1 == " << 2 + r1 << '\n';
  cout << "2-r1 == " << 2 - r1 << '\n';
  cout << "2*r1 == " << 2 * r1 << '\n';
  cout << "2/r1 == " << 2 / r1 << '\n';

  cout << std::boolalpha;
  cout << "r1==r2: " << (r1 == r2) << '\n';
  cout << "r1!=r2: " << (r1 != r2) << '\n';
  cout << "r1>r2: " << (r1 > r2) << '\n';
  cout << "r1<r2: " << (r1 < r2) << '\n';
  cout << "r1>=r2: " << (r1 >= r2) << '\n';
  cout << "r1<=r2: " << (r1 <= r2) << '\n';
}

void test2()
{
  vector<Calc::Rational> vr { { 2, 3 }, { 3, 2 }, { 3, 4 }, { 4, 3 }, { 4, 5 }, { 5, 4 } };
  std::sort(vr.begin(), vr.end());
  for (const auto& r : vr) {
    cout << r << "  ";
  }
  cout << '\n';
}

int main()
{
  test1();
  test2();
}

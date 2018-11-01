#include <iomanip>
#include <iostream>
#include <valarray>

using namespace std;

int main()
{
  constexpr double GM { 0.00028 };
  constexpr double delta_t { 1 };
  const valarray<double> p1 { -1, 0 };
  const valarray<double> p2 { 1, 0 };
  const valarray<double> r0 { 0, 0.5 };
  const valarray<double> v0 { 0.01, 0.01 };

  valarray<double> r { r0 };
  valarray<double> v { v0 };
  for (int i = 0; i < 10000; ++i) {
    cout << setprecision(16) << r[0] << '\t' << r[1] << '\n';
    const valarray<double> r1 { r - p1 };
    const valarray<double> r2 { r - p2 };
    double r12 { r1[0] * r1[0] + r1[1] * r1[1] };
    double r22 { r2[0] * r2[0] + r2[1] * r2[1] };
    valarray<double> a { -(GM / r12) * (r1 / sqrt(r12)) - (GM / r22) * (r2 / sqrt(r22)) };
    v += a * delta_t;
    r += v * delta_t;
  }
}

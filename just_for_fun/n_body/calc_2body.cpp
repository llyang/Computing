#include <iomanip>
#include <iostream>
#include <valarray>

using namespace std;

int main()
{
  constexpr double GM { 0.00028 };
  constexpr double delta_t { 1 };
  const valarray<double> r0 { 1, 0 };
  const valarray<double> v0 { 0, 0.017 };

  valarray<double> r { r0 };
  valarray<double> v { v0 };
  for (int i = 0; i < 1000; ++i) {
    cout << setprecision(16) << r[0] << '\t' << r[1] << '\n';
    double r2 { r[0] * r[0] + r[1] * r[1] };
    valarray<double> a { -(GM / r2) * (r / sqrt(r2)) };
    v += a * delta_t;
    r += v * delta_t;
  }
}

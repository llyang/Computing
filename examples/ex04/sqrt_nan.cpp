#include <cmath>
#include <iostream>

using namespace std;

double my_sqrt(double x)
{
  if (x < 0) {
    return nan("my_sqrt");
  }

  const double error { 1e-6 };
  double a { x };
  double b { 1 };
  while (abs((a - b) / min(a, b)) > error) {
    a = (a + b) / 2;
    b = x / a;
  }
  return a;
}

int main()
{
  double x { 0 };
  cin >> x;
  double y { my_sqrt(x) };
  if (isnan(y)) {
    cout << "my_sqrt error!\n";
    return 1;
  }
  cout << y << '\n';
}


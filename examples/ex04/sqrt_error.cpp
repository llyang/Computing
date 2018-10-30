#include <cmath>
#include <iostream>
using namespace std;

double my_sqrt(double x)
{
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
  cout << my_sqrt(x) << '\n';
}

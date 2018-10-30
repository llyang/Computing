#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class my_sqrt_error {
};

double my_sqrt(double x)
{
  if (x < 0) {
    throw my_sqrt_error {};
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
  vector<int> v { 1, 2, -3, -4, 5 };
  int i { 0 };
  cin >> i;
  try {
    double x { my_sqrt(v.at(i)) };
    cout << "sqrt(v[" << i << "]) = " << x << '\n';
  } catch (out_of_range) {
    cerr << "out of range: i = " << i << '\n';
  } catch (my_sqrt_error) {
    cerr << "my_sqrt_error\n";
  }
}


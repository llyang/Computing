#include <cmath>
#include <iostream>
using namespace std;

class my_sqrt_error {};

double my_sqrt(double x) {
  if (x < 0) {
    throw my_sqrt_error{};
  }
  const double error{1e-6};
  double a{x};
  double b{1};
  while (abs((a - b) / min(a, b)) > error) {
    a = (a + b) / 2;
    b = x / a;
  }
  return a;
}

int main() {
  double x;
  cin >> x;
  try {
    cout << my_sqrt(x) << '\n';
  } catch (my_sqrt_error) {
    cout << "my_sqrt_error\n";
  }
}

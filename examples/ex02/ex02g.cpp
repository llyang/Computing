#include <cmath>
#include <iostream>

using namespace std;

int main() {
  cout << "Please enter a floating-point value: ";
  double x;
  cin >> x;
  cout << "x = " << x << '\n';
  cout << "x+1 = " << x + 1 << '\n';
  cout << "3*x = " << 3 * x << '\n';
  cout << "x squared = " << x * x << '\n';
  cout << "half of x = " << x / 2 << '\n';
  cout << "square root of x = " << sqrt(x) << '\n';
}

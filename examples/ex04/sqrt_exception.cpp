#include <cmath>
#include <iostream>
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

double sqrt_wrapper(double x)
{
  return my_sqrt(x); // 这里可能会甩出一口锅
  // 这里没有try-catch：我不想背锅
}

int main()
{
  double x { 0 };
  cin >> x;
  try {
    cout << sqrt_wrapper(x) << '\n';
  } catch (my_sqrt_error) { // 锅甩到了这里才被接住
    cout << "my_sqrt_error\n";
  }
}


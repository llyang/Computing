#include <cmath>
#include <iostream>

using namespace std;

// 函数声明
double my_sqrt(double);

int main() {
  // 函数调用
  double x{my_sqrt(2)};
  cout << x << '\t' << sqrt(2) << '\n';
  cout << my_sqrt(10000) << '\t' << sqrt(10000) << '\n';
  cout << my_sqrt(0.000001) << '\t' << sqrt(0.000001) << '\n';
}

// 函数定义
double my_sqrt(double x) {
  if (x < 0) {
    return nan("my_sqrt");
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

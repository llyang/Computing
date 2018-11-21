#include <cmath>
#include <iostream>

#include "Complex.h"

using std::cerr;
using std::cin;
using std::cout;

int main()
{
  cout << "Please enter two complex numbers in the form (x,y): \n";
  Calc::Complex z1;
  Calc::Complex z2;
  cin >> z1 >> z2;
  if (!cin) {
    cerr << "wrong input\n";
    return 1;
  }

  cout << "z1 == " << z1 << '\n';
  cout << "z2 == " << z2 << '\n';

  cout << "+z1 == " << +z1 << '\n';
  cout << "-z1 == " << -z1 << '\n';
  cout << "z1+z2 == " << z1 + z2 << '\n';
  cout << "z1-z2 == " << z1 - z2 << '\n';
  cout << "z1*z2 == " << z1 * z2 << '\n';
  cout << "z1/z2 == " << z1 / z2 << '\n';
  cout << "2+z1 == " << 2 + z1 << '\n';
  cout << "2-z1 == " << 2 - z1 << '\n';
  cout << "2*z1 == " << 2 * z1 << '\n';
  cout << "2/z1 == " << 2 / z1 << '\n';

  cout << "z1.conj() == " << z1.conj() << '\n';
  cout << "exp(z1) == " << exp(z1) << '\n';
  // 这里编译器会自动找到正确的exp函数！
  cout << "exp(2.0) == " << exp(2.0) << '\n';
  cout << "z1.norm() == " << z1.norm() << '\n';
  cout << "z1.abs() == " << z1.abs() << '\n';
  cout << "z1.arg() == " << z1.arg() << '\n';

  z1 += z2;
  cout << z1 << '\n';
  z1 -= z2;
  cout << z1 << '\n';
  z1 *= z2;
  cout << z1 << '\n';
  z1 /= z2;
  cout << z1 << '\n';
}

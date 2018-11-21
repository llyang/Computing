#include <cmath>
#include <iostream>

#include "Complex.h"

using std::istream;
using std::ostream;

namespace Calc {

////////////////////////////////////////////////////////////////////////////////

Complex Complex::conj() const
{
  return Complex { x, -y };
}

double Complex::norm() const
{
  return x * x + y * y;
}

double Complex::abs() const
{
  return sqrt(norm());
}

double Complex::arg() const
{
  return atan2(y, x);
}

////////////////////////////////////////////////////////////////////////////////

Complex operator+(Complex z)
{
  return z;
}

Complex operator-(Complex z)
{
  return Complex { -z.real(), -z.imag() };
}

Complex operator+(Complex z1, Complex z2)
{
  return Complex { z1.real() + z2.real(), z1.imag() + z2.imag() };
}

Complex operator-(Complex z1, Complex z2)
{
  return z1 + (-z2);
}

Complex operator*(Complex z1, Complex z2)
{
  double re = z1.real() * z2.real() - z1.imag() * z2.imag();
  double im = z1.real() * z2.imag() + z1.imag() * z2.real();
  return Complex { re, im };
}

Complex operator/(Complex z1, Complex z2)
{
  double n = z2.norm();
  if (n == 0)
    throw Complex::Divide_by_zero {};
  Complex z = z1 * z2.conj();
  return Complex { z.real() / n, z.imag() / n };
}

////////////////////////////////////////////////////////////////////////////////

Complex& Complex::operator+=(Complex z)
{
  (*this) = (*this) + z;
  return (*this);
}

Complex& Complex::operator-=(Complex z)
{
  (*this) = (*this) - z;
  return (*this);
}

Complex& Complex::operator*=(Complex z)
{
  (*this) = (*this) * z;
  return (*this);
}

Complex& Complex::operator/=(Complex z)
{
  (*this) = (*this) / z;
  return (*this);
}

////////////////////////////////////////////////////////////////////////////////

bool operator==(Complex z1, Complex z2)
{
  return z1.real() == z2.real() && z1.imag() == z2.imag();
}

bool operator!=(Complex z1, Complex z2)
{
  return !(z1 == z2);
}

////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& os, Complex z)
{
  return os << '(' << z.real() << ',' << z.imag() << ')';
}

istream& operator>>(istream& is, Complex& z)
{
  char ch1, ch2, ch3;
  double x, y;
  is >> ch1 >> x >> ch2 >> y >> ch3;
  if (!is)
    return is;
  if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
    is.clear(std::ios_base::failbit);
    return is;
  }
  z = Complex { x, y };
  return is;
}

////////////////////////////////////////////////////////////////////////////////

Complex exp(Complex z)
{
  // 注意：由于我们在namespace Calc里面定义了exp函数，外面的exp函数被“挡住”了
  double r = std::exp(z.real());
  return Complex { r * cos(z.imag()), r * sin(z.imag()) };
}

}


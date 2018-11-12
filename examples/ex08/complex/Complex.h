#ifndef _CALC_COMPLEX_H
#define _CALC_COMPLEX_H

#include <iostream>

namespace Calc {

class Complex {
public:
  class Divide_by_zero {
  };

  constexpr Complex(double re = 0.0, double im = 0.0)
      : x { re }
      , y { im }
  {
  }

  double real() const { return x; }
  double imag() const { return y; }

  Complex conj() const;
  double norm() const;
  double abs() const;
  double arg() const;

  Complex& operator+=(Complex z);
  Complex& operator-=(Complex z);
  Complex& operator*=(Complex z);
  Complex& operator/=(Complex z);

private:
  double x, y;
};

Complex operator+(Complex z);
Complex operator-(Complex z);

Complex operator+(Complex z1, Complex z2);
Complex operator-(Complex z1, Complex z2);
Complex operator*(Complex z1, Complex z2);
Complex operator/(Complex z1, Complex z2);

bool operator==(Complex z1, Complex z2);
bool operator!=(Complex z1, Complex z2);

std::ostream& operator<<(std::ostream& os, Complex z);

Complex exp(Complex z);
}

#endif

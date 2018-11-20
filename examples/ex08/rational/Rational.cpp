#include <iostream>

#include "Rational.h"

namespace Calc {

Rational::Rational(int nn, int dd)
{
}

int gcd(int m, int n)
{
}

Rational operator+(Rational r)
{
}

Rational operator-(Rational r)
{
}

Rational operator+(Rational r1, Rational r2)
{
}

Rational operator-(Rational r1, Rational r2)
{
}

Rational operator*(Rational r1, Rational r2)
{
}

Rational operator/(Rational r1, Rational r2)
{
}

bool operator==(Rational r1, Rational r2)
{
}

bool operator!=(Rational r1, Rational r2)
{
}

bool operator>(Rational r1, Rational r2)
{
}

bool operator<(Rational r1, Rational r2)
{
}

bool operator>=(Rational r1, Rational r2)
{
}

bool operator<=(Rational r1, Rational r2)
{
}

/////////////////////////////////////////////////////////////////////////////
// WARNING: do NOT modify the following unless you know what you are doing //
/////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, Rational r)
{
  return os << r.num() << '/' << r.den();
}

std::istream& operator>>(std::istream& is, Rational& r)
{
  char ch;
  int n, d;
  is >> n >> ch >> d;
  if (!is)
    return is;
  if (ch != '/') {
    is.clear(std::ios_base::failbit);
    return is;
  }
  try {
    r = Rational { n, d };
  } catch (Rational::Invalid) {
    is.clear(std::ios_base::failbit);
  }
  return is;
}
}


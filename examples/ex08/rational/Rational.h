#ifndef _RATIONAL_H
#define _RATIONAL_H

#include <iostream>

namespace Calc {

class Rational {
public:
  class Invalid {
  };
  class Divide_by_zero {
  };
  Rational(int nn = 0, int dd = 1);
  int num() const { return n; }
  int den() const { return d; }

private:
  // 提示：每个有理数应该有一个唯一的表示，例如可以约定d>0，且不能再约分
  int n; // 分子
  int d; // 分母
};

int gcd(int m, int n); // |m|和|n|的最大公约数

Rational operator+(Rational r); // 正号 +r
Rational operator-(Rational r); // 负号 -r

Rational operator+(Rational r1, Rational r2); // 加法 r1+r2
Rational operator-(Rational r1, Rational r2); // 减法 r1-r2
Rational operator*(Rational r1, Rational r2); // 乘法 r1*r2
Rational operator/(Rational r1, Rational r2); // 除法 r1/r2

bool operator==(Rational r1, Rational r2); // 相等 r1==r2
bool operator!=(Rational r1, Rational r2); // 不等 r1!=r2
bool operator>(Rational r1, Rational r2); // 大于 r1>r2
bool operator<(Rational r1, Rational r2); // 小于 r1<r2
bool operator>=(Rational r1, Rational r2); // 大于等于 r1>=r2
bool operator<=(Rational r1, Rational r2); // 小于等于 f1<=r2

std::ostream& operator<<(std::ostream& os, Rational r); // 输出 os << r
std::istream& operator>>(std::istream& is, Rational& r); // 输入 is >> r
}

#endif

#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>
class Token {
public:
  char kind;
  double value;
  std::string name;

  Token() {}

  // cppcheck-suppress noExplicitConstructor

  Token(char ch)
      : kind { ch }
      , value { 0 }
  {
  }

  Token(char ch, double val)
      : kind { ch }
      , value { val }
  {
  }

  Token(char ch, const std::string& n)
      : kind { ch }
      , value { 0 }
      , name { n }
  {
  }
};

constexpr char number { '6' };
constexpr char quit { 'q' };
constexpr char print { ';' };

constexpr char name { 'a' };
constexpr char let { 'L' };
const std::string declkey { "let" };

#endif


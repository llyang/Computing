#ifndef _TOKEN_H
#define _TOKEN_H

class Token {
public:
  char kind;
  double value;
};

constexpr char number { '6' };
constexpr char quit { 'q' };
constexpr char print { ';' };

#endif


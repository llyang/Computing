#include <iostream>
#include <stdexcept>

#include "Token_stream.h"

using std::runtime_error;
using std::string;

namespace Calc {

void Token_stream::putback(Token t)
{
  if (full) {
    throw runtime_error { "putback() into a full buffer" };
  }
  buffer = t;
  full = true;
}

Token Token_stream::get()
{
  if (full) {
    full = false;
    return buffer;
  }

  char ch { ' ' };
  ist >> ch;

  switch (ch) {
  case print:
  case quit:
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '=':
    return Token { ch };
  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': {
    ist.putback(ch);
    double val { 0 };
    ist >> val;
    return Token { number, val };
  }
  default:
    if (isalpha(ch)) {
      string s { ch };
      while (ist.get(ch) && (isalpha(ch) || isdigit(ch))) {
        s += ch;
      }
      ist.putback(ch);
      if (s == declkey) {
        return Token { let };
      }
      return Token { name, s };
    }
    throw runtime_error { "Bad token" };
  }
}

void Token_stream::ignore(char c)
// ignore the inputs until the character c
{
  // look into the buffer first
  if (full && c == buffer.kind) {
    full = false;
    return;
  }

  full = false; // clear the buffer

  // search for the character c
  char ch { ' ' };
  while (ist >> ch) {
    if (ch == c)
      return;
  }
}

}

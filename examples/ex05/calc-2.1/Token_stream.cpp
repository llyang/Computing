#include <iostream>
#include <stdexcept>

#include "Token_stream.h"

using std::cin;
using std::runtime_error;

void Token_stream::putback(Token t) {
  if (full) {
    throw runtime_error("putback() into a full buffer");
  }
  buffer = t;
  full = true;
}

Token Token_stream::get() {
  if (full) {
    full = false;
    return buffer;
  }

  char ch;
  cin >> ch;

  switch (ch) {
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
    return Token{ch};
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
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{'6', val};
  }
  default:
    throw runtime_error("Bad token");
  }
}

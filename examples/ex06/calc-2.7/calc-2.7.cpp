/*

Simple calculator

The grammar for input is:

        Statement:
          Expression
          Print
          Quit

        Print:
          ;

        Quit:
          q

        Expression:
          Term
          Expression + Term
          Expression - Term

        Term:
          Primary
          Term * Primary
          Term / Primary
          Term % Primary

        Primary:
          Number
          ( Expression )
          - Primary
          + Primary

        Number:
          floating-point-literal

*/

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "Token.h"
#include "Token_stream.h"

// A global variable, not preferred, just for now
Token_stream ts;

void calculate();
void clean_up_mess();
double expression();
double term();
double primary();

using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::runtime_error;
using std::string;

int main()
{
  try {
    calculate();
    return 0;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}

void clean_up_mess()
{
  ts.ignore(print);
}

void calculate()
{
  const string prompt { "> " };
  const string result { "= " };
  while (cin) {
    try {
      cout << prompt;
      Token t { ts.get() };
      while (t.kind == print) {
        t = ts.get();
      }
      if (t.kind == quit) { // quit
        return;
      }
      ts.putback(t);
      cout << result << expression() << '\n';
    } catch (exception& e) {
      cerr << e.what() << '\n';
      clean_up_mess();
    }
  }
}

// return the value of the next expression
double expression()
{
  double left { term() };
  while (true) {
    Token t { ts.get() };
    switch (t.kind) {
    case '+':
      left += term();
      break;
    case '-':
      left -= term();
      break;
    default:
      ts.putback(t);
      return left;
    }
  }
}

// return the value of the next term
double term()
{
  double left { primary() };
  while (true) {
    Token t { ts.get() };
    switch (t.kind) {
    case '*':
      left *= primary();
      break;
    case '/': {
      double d { primary() };
      if (d == 0) {
        throw runtime_error { "divide by zero" };
      }
      left /= d;
      break;
    }
    case '%': {
      double d { primary() };
      if (d == 0) {
        throw runtime_error { "divide by zero" };
      }
      left = std::fmod(left, d);
      break;
    }
    default:
      ts.putback(t);
      return left;
    }
  }
}

// return the value of the next primary
double primary()
{
  Token t { ts.get() };
  switch (t.kind) {
  case '(': {
    double d { expression() };
    t = ts.get();
    if (t.kind != ')') {
      ts.putback(t);
      throw runtime_error { "')' expected" };
    }
    return d;
  }
  case number:
    return t.value;
  case '-':
    return -primary();
  case '+':
    return primary();
  default:
    ts.putback(t);
    throw runtime_error { "primary expected" };
  }
}


#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Calculator.h"
#include "Token.h"
#include "Token_stream.h"
#include "Variable.h"

using std::cerr;
using std::cout;
using std::exception;
using std::runtime_error;
using std::string;

namespace Calc {

void Calculator::clean_up_mess()
{
  ts.ignore(print);
}

void Calculator::calculate()
{
  const string prompt { "> " };
  const string result { "= " };
  while (ts) {
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
      cout << result << statement() << '\n';
    } catch (exception& e) {
      cerr << e.what() << '\n';
      clean_up_mess();
    }
  }
}

double Calculator::declaration()
{
  Token t { ts.get() };
  if (t.kind != name) {
    throw runtime_error { "name expected in declaration" };
  }
  string var_name { t.name };

  Token t2 { ts.get() };
  if (t2.kind != '=') {
    throw runtime_error { "= missing in declaration of " + var_name };
  }

  double d { expression() };
  vt.define_name(var_name, d);
  return d;
}

double Calculator::statement()
{
  Token t { ts.get() };
  switch (t.kind) {
  case let:
    return declaration();
  default:
    ts.putback(t);
    return expression();
  }
}

// return the value of the next expression
double Calculator::expression()
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
double Calculator::term()
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
double Calculator::primary()
{
  Token t { ts.get() };
  switch (t.kind) {
  case '(': {
    double d { expression() };
    t = ts.get();
    if (t.kind != ')') {
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
  case name:
    return vt.get_value(t.name);
  default:
    ts.putback(t);
    throw runtime_error { "primary expected" };
  }
}

}


#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Calculator.h"
#include "Token.h"
#include "Token_stream.h"
#include "Variable.h"

using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::runtime_error;
using std::string;

namespace Calc {

void clean_up_mess(Token_stream& ts)
{
  ts.ignore(print);
}

void calculate(Token_stream& ts)
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
      cout << result << statement(ts) << '\n';
    } catch (exception& e) {
      cerr << e.what() << '\n';
      clean_up_mess(ts);
    }
  }
}

double declaration(Token_stream& ts)
{
  Token t { ts.get() };
  if (t.kind != name) {
    ts.putback(t);
    throw runtime_error { "name expected in declaration" };
  }
  string var_name { t.name };

  Token t2 { ts.get() };
  if (t2.kind != '=') {
    ts.putback(t2);
    throw runtime_error { "= missing in declaration of " + var_name };
  }

  double d { expression(ts) };
  define_name(var_name, d);
  return d;
}

double statement(Token_stream& ts)
{
  Token t { ts.get() };
  switch (t.kind) {
  case let:
    return declaration(ts);
  default:
    ts.putback(t);
    return expression(ts);
  }
}

// return the value of the next expression
double expression(Token_stream& ts)
{
  double left { term(ts) };
  while (true) {
    Token t { ts.get() };
    switch (t.kind) {
    case '+':
      left += term(ts);
      break;
    case '-':
      left -= term(ts);
      break;
    default:
      ts.putback(t);
      return left;
    }
  }
}

// return the value of the next term
double term(Token_stream& ts)
{
  double left { primary(ts) };
  while (true) {
    Token t { ts.get() };
    switch (t.kind) {
    case '*':
      left *= primary(ts);
      break;
    case '/': {
      double d { primary(ts) };
      if (d == 0) {
        throw runtime_error { "divide by zero" };
      }
      left /= d;
      break;
    }
    case '%': {
      double d { primary(ts) };
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
double primary(Token_stream& ts)
{
  Token t { ts.get() };
  switch (t.kind) {
  case '(': {
    double d { expression(ts) };
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
    return -primary(ts);
  case '+':
    return primary(ts);
  case name:
    return get_value(t.name);
  default:
    ts.putback(t);
    throw runtime_error { "primary expected" };
  }
}

}


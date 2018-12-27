/*

Simple calculator

The grammar for input is:

        Calculation:
          Statement
          Print
          Quit
          Calculation Statement

        Statement:
          Declaration Print
          Expression Print

        Print:
          ;

        Quit:
          q

        Declaration:
          "let" Name '=' Expression

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
          Name

        Number:
          floating-point-literal

*/

#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "Token.h"
#include "Token_stream.h"

using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::map;
using std::out_of_range;
using std::runtime_error;
using std::string;

// A global variable, not preferred, just for now
Token_stream ts;

// Another global variable, just for now
map<string, double> var_table;

void calculate();
void clean_up_mess();

double statement();
double declaration();
double expression();
double term();
double primary();

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

////////////////////////////////////////////////////////////////////////////////

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
      cout << result << statement() << '\n';
    } catch (exception& e) {
      cerr << e.what() << '\n';
      clean_up_mess();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

double get_value(const string& var)
{
  try {
    return var_table.at(var);
  } catch (out_of_range&) {
    throw runtime_error { "get: undefined variable " + var };
  }
}

void set_value(const string& var, double val)
{
  try {
    var_table.at(var) = val;
  } catch (out_of_range&) {
    throw runtime_error { "set: undefined variable " + var };
  }
}

bool is_declared(const string& var)
{
  if (var_table.count(var) > 0) {
    return true;
  } else {
    return false;
  }
}

double define_name(const string& var, double val)
{
  if (is_declared(var)) {
    throw runtime_error { "variable " + var + " is already declared" };
  }
  var_table[var] = val;
  return val;
}

////////////////////////////////////////////////////////////////////////////////

double declaration()
{
  Token t { ts.get() };
  if (t.kind != name) {
    ts.putback(t);
    throw runtime_error { "name expected in declaration" };
  }
  string var_name { t.name };

  t = ts.get();
  if (t.kind != '=') {
    ts.putback(t);
    throw runtime_error { "= missing in declaration of " + var_name };
  }

  double d { expression() };
  define_name(var_name, d);
  return d;
}

double statement()
{
  Token t { ts.get() };
  double r { 0 };
  if (t.kind == let) {
    r = declaration();
  } else {
    ts.putback(t);
    r = expression();
  }

  t = ts.get();
  if (t.kind != print)
    throw runtime_error { "illegal statement" };

  return r;
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
  case name:
    return get_value(t.name);
  default:
    ts.putback(t);
    throw runtime_error { "primary expected" };
  }
}

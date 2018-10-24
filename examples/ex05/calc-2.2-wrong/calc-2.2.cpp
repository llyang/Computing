#include <iostream>
#include <stdexcept>

#include "Token.h"
#include "Token_stream.h"

// A global variable, not preferred, just for now
Token_stream ts;

double expression();
double term();
double primary();

using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::runtime_error;

int main() {
  try {
    double val{0};
    while (cin) {
      Token t = ts.get();
      if (t.kind == 'q') { // quit
        break;
      }
      if (t.kind == ';') { // end of an expression
        cout << "= " << val << '\n';
      } else {
        ts.putback(t);
      }
      val = expression();
    }
  } catch (exception &e) {
    cerr << e.what() << '\n';
    return 1;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}

// return the value of the next expression
// this version is wrong
double expression() {
  double left = term();
  Token t = ts.get();
  switch (t.kind) {
  case '+':
    return left + expression();
  case '-':
    return left - expression();
  default:
    ts.putback(t);
    return left;
  }
}

// return the value of the next term
double term() {
  double left = primary();
  while (true) {
    Token t = ts.get();
    switch (t.kind) {
    case '*':
      left *= primary();
      break;
    case '/': {
      double d = primary();
      if (d == 0) {
        throw runtime_error("divide by zero");
      }
      left /= d;
      break;
    }
    default:
      ts.putback(t);
      return left;
    }
  }
}

// return the value of the next primary
double primary() {
  Token t = ts.get();
  switch (t.kind) {
  case '(': {
    double d = expression();
    t = ts.get();
    if (t.kind != ')') {
      throw runtime_error("')' expected");
    }
    return d;
  }
  case '6':
    return t.value;
  default:
    throw runtime_error("primary expected");
  }
}


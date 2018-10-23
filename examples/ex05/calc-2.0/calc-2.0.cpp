#include <iostream>
#include <stdexcept>

class Token {
public:
  char kind;
  double value;
};

Token get_token();
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
    while (cin) {
      double result = expression();
      cout << "= " << result << '\n';
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
double expression() {
  double left = term();
  while (true) {
    Token t = get_token();
    switch (t.kind) {
    case '+':
      left += term();
      break;
    case '-':
      left -= term();
      break;
    default:
      return left;
    }
  }
}

// return the value of the next term
double term() {
  double left = primary();
  while (true) {
    Token t = get_token();
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
      return left;
    }
  }
}

// return the value of the next primary
double primary() {
  Token t = get_token();
  switch (t.kind) {
  case '(': {
    double d = expression();
    t = get_token();
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

// get the next token from cin
Token get_token() {
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


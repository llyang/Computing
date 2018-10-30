#include <iostream>

using namespace std;

int main()
{
  cout << "Expression: ";

  double lval { 0 };
  double rval { 0 };
  char op { ' ' };
  cin >> lval >> op >> rval;
  if (!cin) {
    throw runtime_error { "input error" };
  }

  double res { 0 };
  switch (op) {
  case '+':
    res = lval + rval;
    break;
  case '-':
    res = lval - rval;
    break;
  case '*':
    res = lval * rval;
    break;
  case '/':
    res = lval / rval;
    break;
  default:
    throw runtime_error { "unknown operator" };
  }

  cout << "Result: " << res << '\n';

  return 0;
}

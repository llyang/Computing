#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
  cout << "Expression (end with ';'): ";

  double lval { 0 };
  cin >> lval;
  if (!cin) {
    throw runtime_error { "no first operand" };
  }

  for (char op; cin >> op;) {
    double rval { 0 };
    if (op != ';') {
      cin >> rval;
    }
    if (!cin) {
      throw runtime_error { "no second operand" };
    }
    switch (op) {
    case '+':
      lval += rval;
      break;
    case '-':
      lval -= rval;
      break;
    case '*':
      lval *= rval;
      break;
    case '/':
      lval /= rval;
      break;
    default:
      cout << "Result: " << lval << '\n';
      return 0;
    }
  }
}

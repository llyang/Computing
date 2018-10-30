#include <iostream>

using namespace std;

int main()
{
  string operation;
  double val1 { 0 };
  double val2 { 0 };

  cout << "Please enter an operation (+,-,*,/,plus,minus,mul,div) followed by two floating-point values:\n";
  while (cin >> operation >> val1 >> val2) {
    double res { 0 };
    if (operation == "+" || operation == "plus") {
      res = val1 + val2;
    } else if (operation == "-" || operation == "minus") {
      res = val1 - val2;
    } else if (operation == "*" || operation == "mul") {
      res = val1 * val2;
    } else if (operation == "/" || operation == "div") {
      res = val1 / val2;
    } else {
      cout << "unknown operator: " << operation << '\n';
      return 1;
    }
    cout << val1 << " " << operation << " " << val2 << " = " << res << '\n';
  }

  return 0;
}

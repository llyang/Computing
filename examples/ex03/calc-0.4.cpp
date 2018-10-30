#include <iostream>
#include <map>

using namespace std;

int main()
{
  string operation;
  double val1 { 0 };
  double val2 { 0 };

  constexpr int plus { 1 };
  constexpr int minus { 2 };
  constexpr int mul { 3 };
  constexpr int div { 4 };

  const map<string, int> operations {
    { "+", plus }, { "plus", plus }, { "-", minus }, { "minus", minus },
    { "*", mul }, { "mul", mul }, { "/", div }, { "div", div }
  };

  cout << "Please enter an operation (+,-,*,/,plus,minus,mul,div) followed by two floating-point values:\n";
  while (cin >> operation >> val1 >> val2) {
    double res { 0 };
    try {
      switch (operations.at(operation)) {
      case plus:
        res = val1 + val2;
        break;
      case minus:
        res = val1 - val2;
        break;
      case mul:
        res = val1 * val2;
        break;
      case div:
        if (val2 == 0) {
          cout << "divide by zero\n";
          return 2;
        }
        res = val1 / val2;
        break;
      }
    } catch (out_of_range) {
      cout << "unknown operator: " << operation << '\n';
      return 1;
    }
    cout << val1 << " " << operation << " " << val2 << " = " << res << '\n';
  }
}

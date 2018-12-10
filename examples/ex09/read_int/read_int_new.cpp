#include <iostream>
#include <stdexcept>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::exception;
using std::runtime_error;
using std::string;

void skip_to_int()
{
  if (cin.fail()) {
    cin.clear();
    for (char ch = ' '; cin >> ch;) {
      if (isdigit(ch) || ch == '-') {
        cin.unget();
        return;
      }
    }
  }
  throw runtime_error { "no input" };
}

int get_int()
{
  int n { 0 };
  while (true) {
    if (cin >> n)
      return n;
    cout << "not a number; try again\n";
    skip_to_int();
  }
}

int get_int(int low, int high,
    const string& greeting, const string& sorry)
{
  cout << greeting << ": [" << low << ',' << high << "]\n";

  while (true) {
    int n { get_int() };
    if (low <= n && n <= high)
      return n;
    cout << sorry << ": [" << low << ',' << high << "]\n";
  }
}

int main()
{
  const string greeting { "Please enter an integer in the range" };
  const string sorry { "out of range; try again" };
  try {
    int n { get_int(1, 10, greeting, sorry) };
    cout << n << '\n';
  } catch (exception& e) {
    cerr << e.what() << '\n';
  }
}

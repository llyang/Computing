#include <iostream>
#include <stdexcept>

using std::cout;
using std::runtime_error;

int factorial(int n)
{
  if (n < 0) {
    throw runtime_error { "factorial: n < 0" };
  } else if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int factorial2(int n)
{
  if (n < 0) {
    throw runtime_error { "factorial: n < 0" };
  } else {
    int r { 1 };
    for (int i = 1; i <= n; ++i) {
      r *= i;
    }
    return r;
  }
}

int main()
{
  cout << factorial(0) << "    " << factorial2(0) << '\n';
  cout << factorial(1) << "    " << factorial2(1) << '\n';
  cout << factorial(10) << "    " << factorial2(10) << '\n';
}

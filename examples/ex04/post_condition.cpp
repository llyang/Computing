#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

double some_function(double a, double b, double c, double d) {
  double r = asin(a + sqrt((b + log(c)) / d));
  if (isnan(r)) {
    throw runtime_error("bad arguments in some_function");
  }
  return r;
}

int main() {
  try {
    cout << some_function(1, 2, 3, 4) << '\n';
  } catch (runtime_error &e) {
    cerr << e.what() << '\n';
  }
}

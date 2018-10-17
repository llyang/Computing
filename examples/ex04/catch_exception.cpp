#include <iostream>
#include <stdexcept>

using namespace std;

class some_error {};

int some_function(int x) {
  if (x < 0) {
    throw(runtime_error("error: x < 0"));
  }
  if (x > 100) {
    throw(out_of_range("error: x > 100"));
  }
  if (x == 10) {
    throw(some_error{});
  }
  return x;
}

int main() {
  for (int x; cin >> x;) {
    try {
      int y = some_function(x);
      cout << y << '\n';
    } catch (exception &e) {
      cerr << e.what() << '\n';
    } catch (...) {
      cerr << "There's something wrong but I don't know why\n";
    }
  }
}

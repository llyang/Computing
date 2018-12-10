#include <iostream>

using std::cout;

int x { 1 };

namespace haha {
int x { 2 };
}

// cppcheck-suppress noConstructor

class A {
public:
  void f()
  {
    cout << "global x: " << ::x << '\n';
    cout << "x in namespace haha: " << haha::x << '\n';
    cout << "x in class A: " << x << '\n';
    int x { 4 };
    cout << "x in function f(): " << x << '\n';
    for (int x = 5; x < 6; ++x) {
      cout << "x in the for statement: " << x << '\n';
      {
        int x { 6 };
        cout << "x in the curly braket: " << x << '\n';
        cout << "global x: " << ::x << '\n';
        cout << "x in namespace haha: " << haha::x << '\n';
        cout << "x in class A: " << this->x << '\n';
      }
    }
  }

private:
  int x { 3 };
};

int main()
{
  A a;
  a.f();
}

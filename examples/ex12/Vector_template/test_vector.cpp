#include <iostream>

#include "Vector.h"

using std::cout;
using std::string;

class A {
public:
  A() { cout << "A::A()\n"; }
  A(const A&) { cout << "A::A(const A&)\n"; }
  A& operator=(const A&)
  {
    cout << "A::operator=(const A&)\n";
    return *this;
  }
  ~A() { cout << "A::~A()\n"; }
};

int main()
{
  Vector<int> v1 { 3, 4, 5 };
  Vector<double> v2 { 3.3, 4.4, 5.5 };
  Vector<string> v3 { "haha", "hehe", "hoho" };
  cout << v1[0] << '\n';
  cout << v2[1] << '\n';
  cout << v3[2] << '\n';

  cout << '\n';

  //Vector<A> v4(5);
}

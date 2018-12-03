#include <iostream>

using std::cout;

class A {
public:
  A()
      : n { 0 }
  {
  }

  A(const A& a)
      : n { a.n }
  {
    cout << "copy constructor\n";
  }

  A& operator=(const A& a)
  {
    n = a.n;
    cout << "copy assigment\n";
    return *this;
  }

  int n;
};

A pass_by_value_and_return_by_value(A a)
{
  ++a.n;
  return a;
}

// Undefined behavior: warning!
A& pass_by_value_and_return_by_reference(A a)
{
  ++a.n;
  return a;
}

A pass_by_reference_and_return_by_value(A& a)
{
  ++a.n;
  return a;
}

A& pass_by_reference_and_return_by_reference(A& a)
{
  ++a.n;
  return a;
}

int main()
{
  A a1;
  cout << "a1.n = " << a1.n << "\n\n";

  cout << "A a2 { pass_by_value_and_return_by_value(a1) };\n";
  A a2 { pass_by_value_and_return_by_value(a1) };
  cout << "a1.n = " << a1.n << '\n';
  cout << "a2.n = " << a2.n << "\n\n";

  cout << "A a3 { pass_by_reference_and_return_by_value(a1) };\n";
  A a3 { pass_by_reference_and_return_by_value(a1) };
  cout << "a1.n = " << a1.n << '\n';
  cout << "a3.n = " << a3.n << "\n\n";

  cout << "++a3.n;\n";
  ++a3.n;
  cout << "a1.n = " << a1.n << '\n';
  cout << "a3.n = " << a3.n << "\n\n";

  cout << "A& a4 { pass_by_reference_and_return_by_reference(a1) };\n";
  A& a4 { pass_by_reference_and_return_by_reference(a1) };
  cout << "a1.n = " << a1.n << '\n';
  cout << "a4.n = " << a4.n << "\n\n";

  cout << "a4 is an alias of a1\n";
  cout << "++a4.n;\n";
  ++a4.n;
  cout << "a1.n = " << a1.n << '\n';
  cout << "a4.n = " << a4.n << "\n\n";

  cout << "A a5 { pass_by_reference_and_return_by_reference(a1) };\n";
  A a5 { pass_by_reference_and_return_by_reference(a1) };
  cout << "a1.n = " << a1.n << '\n';
  cout << "a5.n = " << a5.n << "\n\n";

  cout << "a5 is NOT an alias of a1\n";
  cout << "++a5.n;\n";
  ++a5.n;
  cout << "a1.n = " << a1.n << '\n';
  cout << "a5.n = " << a5.n << "\n\n";

  cout << "A a6; a6 = pass_by_reference_and_return_by_reference(a1);\n";
  A a6;
  a6 = pass_by_reference_and_return_by_reference(a1);
  cout << "a1.n = " << a1.n << '\n';
  cout << "a6.n = " << a6.n << "\n\n";

  cout << "a6 is NOT an alias of a1\n";
  cout << "++a6.n;\n";
  ++a6.n;
  cout << "a1.n = " << a1.n << '\n';
  cout << "a6.n = " << a6.n << "\n\n";
}


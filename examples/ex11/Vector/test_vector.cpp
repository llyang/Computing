#include <iostream>
#include <random>
#include <string>

#include "Vector.h"

using std::cin;
using std::cout;
using std::string;

Vector f1();
Vector f2(int);

void info_vector(const Vector&, const string&);

int main()
{
  cout << "//////// test default contructor\n";
  Vector v1;
  info_vector(v1, "v1");

  cout << "//////// test (int, double) contructor\n";
  Vector v2(3, 3.14);
  info_vector(v2, "v2");

  cout << "//////// test (initializer_list) contructor\n";
  Vector v3 { 1, 1, 2, 3, 5, 8 };
  info_vector(v3, "v3");

  cout << "//////// test copy contructor v4{v3}\n";
  Vector v4 { v3 };
  info_vector(v4, "v4");

  cout << "//////// test copy assignment v1=v3\n";
  v1 = v3;
  info_vector(v1, "v1");

  cout << "//////// test move constructor v5{std::move(v1)}\n";
  Vector v5 { std::move(v1) };
  info_vector(v1, "v1");
  info_vector(v5, "v5");

  cout << "//////// test move assignemt v4=std::move(v5)\n";
  v4 = std::move(v5);
  info_vector(v4, "v4");
  info_vector(v5, "v5");

  cout << "//////// test return-by-move\n";
  cout << "Please input an integer: ";
  int n;
  cin >> n;
  Vector v6 { f2(n) };
  info_vector(v6, "v6");
}

Vector f1()
{
  std::random_device rd;
  std::default_random_engine ran(rd());
  std::uniform_real_distribution<double> ud(0.0, 1.0);

  Vector v(3, ud(ran));

  return v;
}

Vector f2(int n)
{
  Vector v1_in_f2 { f1() };
  Vector v2_in_f2 { f1() };
  if (n > 0) {
    info_vector(v1_in_f2, "v1_in_f2");
    return v1_in_f2;
  } else {
    info_vector(v2_in_f2, "v2_in_f2");
    return v2_in_f2;
  }
}

void info_vector(const Vector& v, const string& n)
{
  cout << n << ".size() = " << v.size() << '\n';
  cout << n << ".data() = " << v.data() << '\n';
  if (v.size() > 0) {
    cout << n << " = {";
    for (size_t i = 0; i < v.size(); ++i) {
      cout << v[i];
      if (i != v.size() - 1)
        cout << ", ";
      else
        cout << "}\n";
    }
  }
  cout << '\n';
}

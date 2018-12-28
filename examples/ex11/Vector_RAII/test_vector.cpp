#include <iostream>
#include <random>
#include <string>

#include "Vector.h"

using std::cin;
using std::cout;
using std::string;

void info_vector(const Vector&, const string&);

int main()
{
  std::random_device rd;
  std::default_random_engine ran(rd());
  std::uniform_real_distribution<double> ud(0.0, 1.0);

  cout << "//////// test push_back\n";
  Vector v1;
  for (int i = 0; i < 2; ++i) {
    v1.push_back(ud(ran));
  }
  info_vector(v1, "v1");

  cout << "//////// test resize\n";
  v1.resize(5, ud(ran));
  info_vector(v1, "v1");

  cout << "//////// test initializer_list\n";
  Vector v2 { ud(ran), ud(ran), ud(ran) };
  info_vector(v2, "v2");

  cout << "//////// copy assignment v2=v1\n";
  v2 = v1;
  info_vector(v1, "v1");
  info_vector(v2, "v2");

  cout << "//////// move assignment v2=std::move(v1)\n";
  v2 = std::move(v1);
  info_vector(v1, "v1");
  info_vector(v2, "v2");
}

void info_vector(const Vector& v, const std::string& n)
{
  std::cout << n << ".size() = " << v.size() << '\n';
  std::cout << n << ".data() = " << v.data() << '\n';
  std::cout << n << ".capacity() = " << v.capacity() << '\n';
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

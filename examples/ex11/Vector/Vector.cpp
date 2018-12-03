#include <algorithm>
#include <iostream>

#include "Vector.h"

Vector::Vector(size_t s, double d)
    : sz { s }
    , elem { new double[s] }
{
  for (size_t i = 0; i < sz; ++i)
    elem[i] = d;
}

Vector::Vector(std::initializer_list<double> lst)
    : sz { lst.size() }
    , elem { new double[sz] }
{
  std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& v)
    : sz { v.sz }
    , elem { new double[v.sz] }
{
  std::cout << "copy constructor\n";
  std::copy(v.elem, v.elem + sz, elem);
}

Vector& Vector::operator=(const Vector& v)
{
  std::cout << "copy assignment\n";
  if (this == &v)
    return *this;
  double* p = new double[v.sz];
  std::copy(v.elem, v.elem + v.sz, p);
  delete[] elem;
  elem = p;
  sz = v.sz;
  return *this;
}

Vector::Vector(Vector&& v)
    : sz { v.sz }
    , elem { v.elem }
{
  std::cout << "move constructor\n";
  v.sz = 0;
  v.elem = nullptr;
}

Vector& Vector::operator=(Vector&& v)
{
  std::cout << "move assignment\n";
  if (this == &v)
    return *this;
  delete[] elem;
  sz = v.sz;
  elem = v.elem;
  v.sz = 0;
  v.elem = nullptr;
  return *this;
}


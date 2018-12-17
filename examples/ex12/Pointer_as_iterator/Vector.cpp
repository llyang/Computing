#include <algorithm>
#include <iostream>

#include "Vector.h"

Vector::Vector()
    : sz { 0 }
    , elem { nullptr }
{
}

Vector::Vector(size_t s, double d)
    : sz { s }
    , elem { sz > 0 ? new double[sz] : nullptr }
{
  for (size_t i = 0; i < sz; ++i)
    elem[i] = d;
}

Vector::Vector(std::initializer_list<double> lst)
    : sz { lst.size() }
    , elem { sz > 0 ? new double[sz] : nullptr }
{
  std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& v)
    : sz { v.sz }
    , elem { sz > 0 ? new double[sz] : nullptr }
{
  std::cout << "copy constructor\n";
  std::copy(v.elem, v.elem + sz, elem);
}

Vector& Vector::operator=(const Vector& v)
{
  std::cout << "copy assignment\n";
  if (this == &v)
    return *this;
  double* p { nullptr };
  if (v.sz > 0) {
    p = new double[v.sz];
    std::copy(v.elem, v.elem + v.sz, p);
  }
  if (elem)
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
  if (elem)
    delete[] elem;
  sz = v.sz;
  elem = v.elem;
  v.sz = 0;
  v.elem = nullptr;
  return *this;
}


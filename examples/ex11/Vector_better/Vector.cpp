#include <algorithm>
#include <iostream>

#include "Vector.h"

Vector::Vector()
    : sz { 0 }
    , elem { nullptr }
    , space { 0 }
{
}

Vector::Vector(size_t s, double d)
    : sz { s }
    , elem { sz > 0 ? new double[sz] : nullptr }
    , space { sz }
{
  for (size_t i = 0; i < sz; ++i)
    elem[i] = d;
}

Vector::Vector(std::initializer_list<double> lst)
    : sz { lst.size() }
    , elem { sz > 0 ? new double[sz] : nullptr }
    , space { sz }
{
  std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& v)
    : sz { v.sz }
    , elem { sz > 0 ? new double[sz] : nullptr }
    , space { sz }
{
  std::copy(v.elem, v.elem + sz, elem);
}

Vector& Vector::operator=(const Vector& v)
{
  if (this == &v)
    return *this;

  if (v.sz > space)
    reserve(v.sz);

  std::copy(v.elem, v.elem + v.sz, elem);
  sz = v.sz;
  return *this;
}

Vector::Vector(Vector&& v)
    : sz { v.sz }
    , elem { v.elem }
    , space { v.space }
{
  v.sz = 0;
  v.elem = nullptr;
  v.space = 0;
}

Vector& Vector::operator=(Vector&& v)
{
  if (this == &v)
    return *this;

  if (elem)
    delete[] elem;
  sz = v.sz;
  elem = v.elem;
  space = v.space;

  v.sz = 0;
  v.elem = nullptr;
  v.space = 0;

  return *this;
}

void Vector::reserve(size_t newalloc)
{
  if (newalloc <= space)
    return;
  double* p { new double[newalloc] };
  for (size_t i = 0; i < sz; ++i)
    p[i] = elem[i];
  if (elem)
    delete[] elem;
  elem = p;
  space = newalloc;
}

void Vector::resize(size_t newsize, double d)
{
  reserve(newsize);
  for (size_t i = sz; i < newsize; ++i)
    elem[i] = d;
  sz = newsize;
}

void Vector::push_back(double d)
{
  if (space == 0)
    reserve(8);
  else if (sz == space)
    reserve(2 * space);
  elem[sz] = d;
  ++sz;
}


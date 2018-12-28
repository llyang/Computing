#include <algorithm>
#include <iostream>

#include "Vector.h"

Vector_base::Vector_base(size_t sp)
    : elem { sp > 0 ? new double[sp] : nullptr }
    , space { sp }
{
}

Vector_base::Vector_base(Vector_base&& v) noexcept
    : elem { v.elem }
    , space { v.space }
{
  v.elem = nullptr;
  v.space = 0;
}

Vector_base& Vector_base::operator=(Vector_base&& v) noexcept
{
  if (this == &v)
    return *this;

  delete[] elem;
  elem = v.elem;
  space = v.space;

  v.elem = nullptr;
  v.space = 0;

  return *this;
}

Vector::Vector()
    : Vector_base { 0 }
    , sz { 0 }
{
}

Vector::Vector(size_t s, double d)
    : Vector_base { s }
    , sz { s }
{
  for (size_t i = 0; i < sz; ++i)
    elem[i] = d;
}

Vector::Vector(std::initializer_list<double> lst)
    : Vector_base { lst.size() }
    , sz { lst.size() }
{
  std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& v)
    : Vector_base { v.size() }
    , sz { v.size() }
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

Vector::Vector(Vector&& v) noexcept
    : Vector_base { std::move(v) }
    , sz { v.sz }
{
  v.sz = 0;
}

Vector& Vector::operator=(Vector&& v) noexcept
{
  if (this == &v)
    return *this;

  Vector_base b { 0 };
  std::swap<Vector_base>(b, v);
  std::swap<Vector_base>(*this, b);
  sz = v.sz;
  v.sz = 0;

  return *this;
}

void Vector::reserve(size_t newalloc)
{
  if (newalloc <= space)
    return;
  Vector_base b { newalloc };
  if (elem)
    std::copy(b.elem, b.elem + sz, elem);
  std::swap<Vector_base>(*this, b);
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

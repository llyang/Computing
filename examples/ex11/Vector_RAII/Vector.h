#ifndef _VECTOR_H
#define _VECTOR_H

#include <initializer_list>
#include <string>

class Vector_base {
public:
  explicit Vector_base(std::size_t sp);

  Vector_base(const Vector_base&) = delete;
  Vector_base& operator=(const Vector_base&) = delete;

  Vector_base(Vector_base&& v) noexcept;
  Vector_base& operator=(Vector_base&& v) noexcept;

  ~Vector_base()
  {
    delete[] elem;
  }

  double* elem;
  std::size_t space;
};

class Vector : private Vector_base {
public:
  Vector();
  explicit Vector(std::size_t s, double d = 0.0);
  Vector(std::initializer_list<double> lst);

  std::size_t size() const { return sz; }
  double* data() { return elem; }
  const double* data() const { return elem; }

  double& operator[](std::size_t i) { return elem[i]; }
  double operator[](std::size_t i) const { return elem[i]; }

  Vector(const Vector& v);
  Vector& operator=(const Vector& v);

  Vector(Vector&& v) noexcept;
  Vector& operator=(Vector&& v) noexcept;

  void reserve(std::size_t newalloc);
  std::size_t capacity() const { return space; }
  void resize(std::size_t newsize, double d = 0.0);
  void push_back(double d);

private:
  std::size_t sz;
};

#endif

#ifndef _VECTOR_H
#define _VECTOR_H

#include <initializer_list>

class Vector {
public:
  Vector();
  explicit Vector(std::size_t s, double d = 0.0);
  Vector(std::initializer_list<double> lst);

  ~Vector()
  {
    delete[] elem;
  }

  std::size_t size() const { return sz; }
  double* data() { return elem; }
  const double* data() const { return elem; }

  double& operator[](std::size_t i) { return elem[i]; }
  double operator[](std::size_t i) const { return elem[i]; }

  Vector(const Vector& v);
  Vector& operator=(const Vector& v);

  Vector(Vector&& v) noexcept;
  Vector& operator=(Vector&& v) noexcept;

private:
  std::size_t sz;
  double* elem;
};

#endif

#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
public:
  explicit Vector(size_t s = 0, double d = 0.0);
  ~Vector() { delete[] elem; }

  Vector(std::initializer_list<double> lst);

  size_t size() const { return sz; }

  double& operator[](size_t i) { return elem[i]; }
  double operator[](size_t i) const { return elem[i]; }

  Vector(const Vector& v);
  Vector& operator=(const Vector& v);

  Vector(Vector&& v);
  Vector& operator=(Vector&& v);

private:
  size_t sz;
  double* elem;
};

#endif

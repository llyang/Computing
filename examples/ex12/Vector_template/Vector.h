#ifndef _VECTOR_H
#define _VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <memory>

template <typename T>
class Vector {
public:
  Vector();
  explicit Vector(std::size_t s, T t = T());
  Vector(std::initializer_list<T> lst);

  ~Vector();

  std::size_t size() const { return sz; }
  T* data() { return elem; }
  const T* data() const { return elem; }

  T& operator[](std::size_t i) { return elem[i]; }
  T operator[](std::size_t i) const { return elem[i]; }

  Vector(const Vector& v);
  Vector& operator=(const Vector& v);

  Vector(Vector&& v) noexcept;
  Vector& operator=(Vector&& v) noexcept;

private:
  std::allocator<T> alloc;
  std::size_t sz;
  T* elem;
};

// Note: templates are incompatible with separate compilation,
// so we have to put the implementation in the header file

template <typename T>
Vector<T>::~Vector()
{
  if (elem) {
    for (size_t i = 0; i < sz; ++i)
      alloc.destroy(&elem[i]);
    alloc.deallocate(elem, sz);
  }
}

template <typename T>
Vector<T>::Vector()
    : sz { 0 }
    , elem { nullptr }
{
}

template <typename T>
Vector<T>::Vector(size_t s, T t)
    : sz { s }
    , elem { sz > 0 ? alloc.allocate(sz) : nullptr }
{
  for (size_t i = 0; i < sz; ++i)
    alloc.construct(&elem[i], t);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst)
    : sz { lst.size() }
    , elem { sz > 0 ? alloc.allocate(sz) : nullptr }
{
  std::uninitialized_copy(lst.begin(), lst.end(), elem);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v)
    : sz { v.sz }
    , elem { sz > 0 ? alloc.allocate(sz) : nullptr }
{
  std::uninitialized_copy(v.elem, v.elem + sz, elem);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
  if (this == &v)
    return *this;
  T* p { nullptr };
  if (v.sz > 0) {
    p = alloc.allocate(v.sz);
    std::uninitialized_copy(v.elem, v.elem + v.sz, p);
  }
  if (elem) {
    for (size_t i = 0; i < sz; ++i)
      alloc.destroy(&elem[i]);
    alloc.deallocate(elem, sz);
  }
  elem = p;
  sz = v.sz;
  return *this;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v) noexcept
    : sz { v.sz }
    , elem { v.elem }
{
  v.sz = 0;
  v.elem = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept
{
  if (this == &v)
    return *this;
  if (elem) {
    for (size_t i = 0; i < sz; ++i)
      alloc.destroy(&elem[i]);
    alloc.deallocate(elem, sz);
  }
  sz = v.sz;
  elem = v.elem;
  v.sz = 0;
  v.elem = nullptr;
  return *this;
}

#endif


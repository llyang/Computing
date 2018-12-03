#ifndef VECTOR_REF_GUARD
#define VECTOR_REF_GUARD

#include <vector>

namespace Graph_lib {

template <class T>
class Vector_ref {
public:
  Vector_ref() {}
  Vector_ref(T* t)
  {
    if (t)
      push_back(t);
  }
  ~Vector_ref()
  {
    for (auto p : owned)
      delete p;
  }

  void push_back(T& s) { v.push_back(&s); }
  void push_back(T* p)
  {
    v.push_back(p);
    owned.push_back(p);
  }

  T& operator[](int i) { return *v[i]; }
  const T& operator[](int i) const { return *v[i]; }
  int size() const { return v.size(); }

private:
  std::vector<T*> v;
  std::vector<T*> owned;
};

} // namespace Graph_lib

#endif


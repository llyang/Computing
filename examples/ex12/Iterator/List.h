#ifndef _LIST_H
#define _LIST_H

#include <initializer_list>

struct Link {
  double val;
  Link* prev;
  Link* succ;
};

class List {
public:
  class iterator;

  List()
      : head { nullptr }
      , tail { nullptr }
  {
  }
  explicit List(std::initializer_list<double> lst);
  ~List();

  iterator begin();
  iterator end();
  iterator begin() const;
  iterator end() const;

  iterator insert(iterator it, double val);
  iterator erase(iterator it);
  void push_back(double val);
  void push_front(double val);

  List(const List&) = delete;
  List& operator=(const List&) = delete;
  List(List&&) = delete;
  List& operator=(List&&) = delete;

private:
  Link* head;
  Link* tail;
};

class List::iterator {
public:
  friend class List; // allow List to access curr

  explicit iterator(Link* p)
      : curr { p }
  {
  }

  iterator& operator++()
  {
    curr = curr->succ;
    return *this;
  }

  double& operator*() { return curr->val; }

  bool operator==(const iterator& it) const { return curr == it.curr; }
  bool operator!=(const iterator& it) const { return curr != it.curr; }

private:
  Link* curr;
};

#endif


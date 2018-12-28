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
  List()
      : head { nullptr }
      , tail { nullptr }
  {
  }
  List(std::initializer_list<double> lst);
  ~List();

  Link* begin() const { return head; }
  Link* end() const { return nullptr; }

  Link* insert(Link* l, double val);
  Link* erase(Link* l);
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

#endif


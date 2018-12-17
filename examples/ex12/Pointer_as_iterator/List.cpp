#include <initializer_list>

#include "List.h"

List::List(std::initializer_list<double> lst)
    : head { nullptr }
    , tail { nullptr }
{
  for (auto x : lst) {
    push_back(x);
  }
}

List::~List()
{
  while (head) {
    erase(head);
  }
}

Link* List::insert(Link* l, double val)
{
  Link* p = new Link { val, nullptr, l };
  if (l == nullptr) { // insert after the tail
    p->prev = tail;
    if (tail) {
      tail->succ = p;
    } else {
      head = p; // was empty List
    }
    tail = p;
    return p;
  }
  // normal insertion
  p->prev = l->prev;
  l->prev = p;
  if (p->prev) {
    p->prev->succ = p;
  } else {
    head = p; // l was head
  }
  return p;
}

Link* List::erase(Link* l)
{
  if (l == nullptr)
    return l;
  if (l->succ) {
    l->succ->prev = l->prev;
  } else {
    tail = l->prev; // l was tail
  }
  if (l->prev) {
    l->prev->succ = l->succ;
  } else {
    head = l->succ; // l was head
  }
  Link* p = l->succ;
  delete l;
  return p;
}

void List::push_back(double val)
{
  insert(end(), val);
}

void List::push_front(double val)
{
  insert(begin(), val);
}


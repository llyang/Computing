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
  while (begin() != end()) {
    erase(begin());
  }
}

List::iterator List::begin()
{
  return iterator { head };
}

List::iterator List::end()
{
  return iterator { nullptr };
}

List::iterator List::begin() const
{
  return iterator { head };
}

List::iterator List::end() const
{
  return iterator { nullptr };
}

List::iterator List::insert(List::iterator it, double val)
{
  Link* l { it.curr };
  Link* p { new Link { val, nullptr, l } };
  if (it == end()) { // insert after the tail
    p->prev = tail;
    if (tail) {
      tail->succ = p;
    } else {
      head = p; // was empty List
    }
    tail = p;
    return iterator { p };
  }
  // normal insertion
  p->prev = l->prev;
  l->prev = p;
  if (p->prev) {
    p->prev->succ = p;
  } else {
    head = p; // l was head
  }
  return iterator { p };
}

List::iterator List::erase(List::iterator it)
{
  if (it == end())
    return it;
  Link* l { it.curr };
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
  Link* p { l->succ };
  delete l;
  return iterator { p };
}

void List::push_back(double val)
{
  insert(end(), val);
}

void List::push_front(double val)
{
  insert(begin(), val);
}


#include <iostream>

#include "List.h"

using std::cout;

void print_list(const List& l)
{
  for (Link* p = l.begin(); p != l.end(); p = p->succ) {
    cout << p->val << '\n';
  }
  cout << '\n';
}

int main()
{
  List l1 { 10, 11, 12 };
  print_list(l1);

  l1.push_back(13);
  l1.push_front(8);
  l1.insert(l1.begin()->succ, 9);
  print_list(l1);

  l1.erase(l1.begin()->succ->succ);
  print_list(l1);
}


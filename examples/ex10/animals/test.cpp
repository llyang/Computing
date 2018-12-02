#include <iostream>
#include <vector>

#include "Animal.h"

using std::cout;
using std::vector;

int main()
{
  Cat a { "Bob", 20 };
  Dog b { "Bolt", 10 };
  Cat c { "Tom", 40 };
  Dog d { "Spike", 30 };
  vector<Animal*> animals { &a, &b, &c, &d };
  for (auto p : animals) {
    cout << "The weight of " << p->name() << " is " << p->weight() << '\n';
    p->eat();
    cout << "The weight of " << p->name() << " is now " << p->weight() << '\n';
    p->talk();
    cout << '\n';
  }
}


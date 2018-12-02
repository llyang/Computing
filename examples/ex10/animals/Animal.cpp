#include <iostream>

#include "Animal.h"

using std::cout;

void Animal::eat()
{
  ++weight_;
}

void Cat::eat()
{
  Animal::eat();
  cout << name_ << " is eating cat food...\n";
}

void Cat::talk()
{
  cout << name_ << " says: meow~~~ meow~~~\n";
}

void Dog::eat()
{
  Animal::eat();
  cout << name_ << " is eating dog food\n";
}

void Dog::talk()
{
  cout << name_ << " says: woof woof\n";
}


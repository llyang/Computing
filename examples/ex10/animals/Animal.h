#ifndef _ANIMAL_H
#define _ANIMAL_H

#include <string>

class Animal {
public:
  virtual void eat();
  virtual void talk() = 0;

  std::string name() const { return name_; }
  int weight() const { return weight_; }

  virtual ~Animal() {}

protected:
  Animal(const std::string& name, int weight)
      : name_ { name }
      , weight_ { weight }
  {
  }

protected:
  std::string name_;
  int weight_;
};

class Cat : public Animal {
public:
  void eat() override;
  void talk() override;

  Cat(const std::string& name, int weight)
      : Animal { name, weight }
  {
  }
};

class Dog : public Animal {
public:
  void eat() override;
  void talk() override;

  Dog(const std::string& name, int weight)
      : Animal { name, weight }
  {
  }
};

#endif


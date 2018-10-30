#include <iostream>

class Token {
public:
  char kind; // '+', '-', '*', '/', '%', '6'
  double value;
};

using std::cout;

int main()
{
  Token t1 { '+' }; // t1.kind = '+'
  cout << "t1: " << t1.kind << " " << t1.value << '\n';

  Token t2 { '6', 3.2 }; // t2.kind = '6', t2.value = 3.2
  cout << "t2: " << t2.kind << " " << t2.value << '\n';

  Token t3 { t2 };
  cout << "t3: " << t3.kind << " " << t3.value << '\n';

  t3 = t1;
  cout << "t3 is now the same as t1: ";
  cout << t3.kind << " " << t3.value << '\n';

  t1.kind = '6';
  t1.value = 5.4;
  cout << "t1 is now: " << t1.kind << " " << t1.value << '\n';
}

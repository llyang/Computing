#include <iostream>

using namespace std;

int main()
{
  int i { 0 };
  while (i < 100) {
    cout << i << '\t' << i * i << '\n';
    ++i;
  }
}

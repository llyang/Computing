#include <cctype>
#include <iostream>

using std::cin;
using std::cout;

int main()
{
  while (cin) {
    char ch;
    cin.get(ch);
    cout << ch << '\t' << int { ch } << '\t'
         << "isalpha: " << isalpha(ch) << '\t'
         << "isdigit: " << isdigit(ch) << '\t'
         << "isspace: " << isspace(ch) << '\t'
         << '\n';
  }
}


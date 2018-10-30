#include <iostream>
using namespace std;

int main()
{
  cout << "Please input your first name and age (followed by 'enter'): ";
  string first_name { "???" };
  int age { -1 };
  cin >> first_name >> age; // 输入一个字符串和一个整数

  cout << "Hello, " << first_name << "! You are " << age << " years old!\n";

  return 0;
}

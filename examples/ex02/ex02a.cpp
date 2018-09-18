#include <iostream>
using namespace std; // 使用cout、cin、string等标准库更方便

int main() {
  cout << "Please input your first name (followed by 'enter'): ";
  string first_name; // 定义string型变量first_name；string代表字符串
  cin >> first_name; // 从键盘输入一个字符串到变量first_name

  cout << "Please input your last name (followed by 'enter'): ";
  string last_name;
  cin >> last_name;

  // 字符串连接用加号运算符+
  // 变量初始化用花括号{}
  string full_name{first_name + " " + last_name};

  cout << "Hello, " << full_name << "!\n";

  return 0;
}

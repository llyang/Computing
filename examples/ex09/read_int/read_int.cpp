#include <iostream>

using std::cin;
using std::cout;
using std::runtime_error;

int main()
{
  cout << "Please enter an integer in the range [1,10]:\n";
  int n { 0 };
  while (true) {
    cin >> n;
    if (cin) { // 成功读入一个整数！下面检查范围
      if (1 <= n && n <= 10)
        break; // 成功！跳出循环
      cout << "out of range; try again\n";
    } else if (cin.fail()) { // 不是整数
      cin.clear();
      cout << "not a number; try again\n";
      for (char ch; cin >> ch && !isdigit(ch);)
        ; // 忽略非数字
      if (!cin)
        throw runtime_error { "你逗我？" };
      cin.unget();
    } else {
      throw runtime_error { "no input" };
    }
  }
  cout << n << '\n';
}

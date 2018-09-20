#include <iomanip>
#include <iostream>

using namespace std;

int main() {

  // 定义变量并初始化
  int number_of_apples{10}; // 整数
  double pi{3.14};          // 双精度浮点数
  char c{'a'};              // 字符
  string name{"Voldemort"}; // 字符串
  bool is_holiday{false};   // 布尔型

  cout << number_of_apples << '\n';
  cout << pi << '\n';
  cout << c << '\n';
  cout << name << '\n';
  cout << boolalpha << is_holiday << '\n';

  cout << '\n';

  // 给变量赋值（改变数据）
  number_of_apples = 20;
  pi = 3.14159;
  c = 'b';
  name = "Harry Potter";
  is_holiday = true;

  cout << number_of_apples << '\n';
  cout << pi << '\n';
  cout << c << '\n';
  cout << name << '\n';
  cout << boolalpha << is_holiday << '\n';

  cout << '\n';

  cout << setprecision(18) << pi << '\n';
  cout << setprecision(18) << pi + 0.02 - 0.01 - 0.01 << '\n';
}

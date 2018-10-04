#include <iostream>

using namespace std;

int main() {
  string previous = " "; // 初始化
  string current;
  while (cin >> current) { // 遇到EOF就终止循环
    if (previous == current) {
      cout << "repeated word: " << current << '\n';
    }
    previous = current; // 赋值
  }
}

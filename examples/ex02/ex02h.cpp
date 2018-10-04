#include <iostream>

using namespace std;

int main() {
  cout << "Please input two integers\n";
  int first;
  int second;
  cin >> first >> second;
  if (first == second) {
    cout << "They are equal!\n";
  } else if (first < second) {
    cout << first << " is smaller than " << second << "!\n";
  } else {
    cout << first << " is larger than " << second << "!\n";
  }
}

#include <iostream>

using namespace std;

int main() {
  cout << "Please input your full name (followed by 'enter'): ";
  string full_name{"???"};
  getline(cin, full_name);
  cout << "Hello, " << full_name << "!\n";
}

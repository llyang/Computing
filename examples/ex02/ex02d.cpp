#include <iostream>

using namespace std;

int main() {
  cout << "Please input your full name (followed by 'enter'): ";
  string first_name{"???"}, last_name{"???"};
  cin >> first_name >> last_name;

  string full_name{first_name + " " + last_name};

  cout << "Hello, " << full_name << "!\n";
}

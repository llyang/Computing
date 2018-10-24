#include <iostream>

using namespace std;

void hanoi(int n, string from, string to, string other) {
  if (n < 1) {
    return;
  }
  hanoi(n - 1, from, other, to);
  cout << "Move disc " << n << " from " << from << " to " << to << '\n';
  hanoi(n - 1, other, to, from);
}

int main() { hanoi(3, "A", "B", "C"); }


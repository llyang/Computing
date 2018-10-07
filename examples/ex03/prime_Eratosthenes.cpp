#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  constexpr int max{100};
  vector<bool> is_prime(max + 1, true);

  for (int i = 2; i <= sqrt(max); ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j <= max; j += i) {
        is_prime[j] = false;
      }
    }
  }

  for (int i = 2; i <= max; ++i) {
    if (is_prime[i]) {
      cout << i << '\n';
    }
  }
}

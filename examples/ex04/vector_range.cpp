#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
{
  vector<int> v { 1, 2, 3, 4, 5 };
  int i { 0 };
  cin >> i;
  try {
    int n { v.at(i) };
    cout << "v[" << i << "] = " << n << '\n';
  } catch (out_of_range) {
    cout << "out of range: i = " << i << '\n';
  }
}


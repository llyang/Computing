#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> v { 1, 2, 3, 4, 5 };
  int i { 0 };
  cin >> i;
  // cout << v[i] << '\n';
  cout << v.at(i) << '\n';
}

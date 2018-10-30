#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<double> temps;
  for (double temp; cin >> temp;) {
    temps.push_back(temp);
  }

  double sum { 0 };
  for (double x : temps) {
    sum += x;
  }
  cout << "Average temperature: " << sum / temps.size() << '\n';

  sort(temps.begin(), temps.end());
  cout << "Lowest temperature: " << temps[0] << '\n';
  cout << "Highest temperature: " << temps[temps.size() - 1] << '\n';
}

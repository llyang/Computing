#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> temps;

  for (double temp; cin >> temp;) {
    temps.push_back(temp);
  }

  double sum{0};
  double high_temp{0};
  double low_temp{0};

  for (double x : temps) {
    if (x > high_temp) {
      high_temp = x;
    }
    if (x < low_temp) {
      low_temp = x;
    }
    sum += x;
  }

  cout << "High temperature: " << high_temp << '\n';
  cout << "Low temperature: " << low_temp << '\n';
  cout << "Average temperature: " << sum / temps.size() << '\n';
}

#include <iostream>
#include <vector>

using namespace std;

void sort_vector_double(vector<double> &v) {
  bool finished = false;
  while (!finished) {
    finished = true;
    for (int i = 0; i < v.size() - 1; ++i) {
      if (v[i] > v[i + 1]) {
        double temp = v[i];
        v[i] = v[i + 1];
        v[i + 1] = temp;
        finished = false;
      }
    }
  }
}

int main() {
  vector<double> temps;
  for (double temp; cin >> temp;) {
    temps.push_back(temp);
  }

  sort_vector_double(temps);

  cout << "Lowest temperature: " << temps[0] << '\n';
  cout << "Highest temperature: " << temps[temps.size() - 1] << '\n';
}

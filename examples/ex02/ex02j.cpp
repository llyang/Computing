#include <iostream>

using namespace std;

int main()
{
  int number_of_words { 0 };
  string previous { " " };
  string current;
  while (cin >> current) {
    ++number_of_words;
    if (previous == current) {
      cout << "word number " << number_of_words << " repeated: ";
      cout << current << '\n';
    }
    previous = current;
  }
}

#include <iostream>
#include <map>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::map;
using std::out_of_range;
using std::string;

int main()
{
  map<string, double> var_table {
    { "x", 1.2 },
    { "y", -2.5 },
    { "z", 4.8 }
  };

  for (auto& var : var_table) {
    cout << var.first << " = " << var.second << '\n';
  }

  cout << "x = " << var_table["x"] << '\n';

  cout << "w = " << var_table["w"] << '\n';

  var_table["t"] = 10.9;
  cout << "t = " << var_table["t"] << '\n';

  try {
    double a = var_table.at("a");
    cout << "a = " << a << '\n';
  } catch (out_of_range& e) {
    cerr << e.what() << '\n';
  }
}


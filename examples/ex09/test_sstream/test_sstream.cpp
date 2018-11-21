#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::string;

double str_to_double(string s)
{
  std::istringstream iss { s };
  double d;
  iss >> d;
  if (!iss)
    throw std::runtime_error { "cannot convert to double: " + s };
  return d;
}

int main()
{
  std::ostringstream oss;
  oss << 3.14 << " " << 3.4 << " haha";
  string s { oss.str() };
  cout << s << '\n';
  double d { str_to_double(s) };
  cout << d << '\n';
  return 0;
}

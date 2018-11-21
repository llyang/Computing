#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Calculator.h"

using std::cerr;
using std::cin;
using std::cout;
using std::ifstream;
using std::string;

int main()
{
  cout << "Please enter the name of the input file: ";
  string fname;
  cin >> fname;

  ifstream ifs { fname };
  if (!ifs) {
    cerr << "cannot open file " + fname << '\n';
    return 1;
  }

  Calc::Calculator calc { ifs };

  try {
    calc.calculate();
    return 0;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}


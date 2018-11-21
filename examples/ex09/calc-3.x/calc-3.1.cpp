#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Calculator.h"

using std::cerr;
using std::ifstream;
using std::string;

int main()
{
  string fname { "input1.txt" };
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


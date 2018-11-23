#include <iostream>
#include <stdexcept>

#include "Calculator.h"

using std::cerr;

int main()
{
  Calc::Calculator calc; // contains ts and vt

  try {
    calc.calculate();
    return 0;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}


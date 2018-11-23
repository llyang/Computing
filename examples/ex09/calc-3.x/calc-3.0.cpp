#include <iostream>
#include <stdexcept>

#include "Calculator.h"

using std::cerr;

int main()
{
  Calc::Calculator calc; // by default ist = cin

  try {
    calc.calculate();
    return 0;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}


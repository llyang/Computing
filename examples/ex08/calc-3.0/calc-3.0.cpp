/*

Simple calculator

The grammar for input is:

        Calculation:
          Statement
          Print
          Quit
          Calculation Statement

        Statement:
          Declaration
          Expression

        Print:
          ;

        Quit:
          q

        Expression:
          Term
          Expression + Term
          Expression - Term

        Term:
          Primary
          Term * Primary
          Term / Primary
          Term % Primary

        Primary:
          Number
          ( Expression )
          - Primary
          + Primary

        Number:
          floating-point-literal

*/

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


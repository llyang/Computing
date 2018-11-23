#include <iostream>
#include <stdexcept>

#include "Calculator.h"
#include "Token_stream.h"

using std::cerr;

int main()
{
  // a local variable, passed by reference between functions
  Calc::Token_stream ts;

  try {
    Calc::calculate(ts);
    return 0;
  } catch (...) {
    cerr << "unknown error\n";
    return 2;
  }
}


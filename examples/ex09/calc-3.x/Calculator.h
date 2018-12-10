#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include <iostream>

#include "Token_stream.h"
#include "Variable.h"

namespace Calc {

class Calculator {
public:
  explicit Calculator(std::istream& is = std::cin)
      : ts { is }
  {
  }

  void calculate();

private:
  Token_stream ts;
  Var_table vt;

  void clean_up_mess();

  double statement();
  double declaration();
  double expression();
  double term();
  double primary();
};
}

#endif


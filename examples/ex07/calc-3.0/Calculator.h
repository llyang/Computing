#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "Token_stream.h"

namespace Calc {

void calculate(Token_stream& ts);
void clean_up_mess(Token_stream& ts);

double statement(Token_stream& ts);
double declaration(Token_stream& ts);
double expression(Token_stream& ts);
double term(Token_stream& ts);
double primary(Token_stream& ts);

}

#endif


#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <string>

namespace Calc {

double get_value(std::string);
void set_value(std::string, double);
bool is_declared(std::string);
double define_name(std::string, double);
}

#endif


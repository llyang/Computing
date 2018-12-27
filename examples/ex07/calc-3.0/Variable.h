#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <string>

namespace Calc {

double get_value(const std::string&);
void set_value(const std::string&, double);
bool is_declared(const std::string&);
double define_name(const std::string&, double);
}

#endif


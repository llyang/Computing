#include <map>
#include <stdexcept>
#include <string>

#include "Variable.h"

using std::map;
using std::out_of_range;
using std::runtime_error;
using std::string;

namespace Calc {

double Var_table::get_value(string var)
{
  try {
    return table.at(var);
  } catch (out_of_range&) {
    throw runtime_error { "get: undefined variable " + var };
  }
}

void Var_table::set_value(string var, double val)
{
  try {
    table.at(var) = val;
  } catch (out_of_range&) {
    throw runtime_error { "set: undefined variable " + var };
  }
}

bool Var_table::is_declared(string var)
{
  if (table.count(var) > 0) {
    return true;
  } else {
    return false;
  }
}

double Var_table::define_name(string var, double val)
{
  if (is_declared(var)) {
    throw runtime_error { "variable " + var + " is already declared" };
  }
  table[var] = val;
  return val;
}

}

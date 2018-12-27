#include <map>
#include <stdexcept>
#include <string>

#include "Variable.h"

using std::map;
using std::out_of_range;
using std::runtime_error;
using std::string;

namespace Calc {

// still not ideal, just for now
map<string, double> var_table;

double get_value(const string& var)
{
  try {
    return var_table.at(var);
  } catch (out_of_range&) {
    throw runtime_error { "get: undefined variable " + var };
  }
}

void set_value(const string& var, double val)
{
  try {
    var_table.at(var) = val;
  } catch (out_of_range&) {
    throw runtime_error { "set: undefined variable " + var };
  }
}

bool is_declared(const string& var)
{
  if (var_table.count(var) > 0) {
    return true;
  } else {
    return false;
  }
}

double define_name(const string& var, double val)
{
  if (is_declared(var)) {
    throw runtime_error { "variable " + var + " is already declared" };
  }
  var_table[var] = val;
  return val;
}

}

#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <map>
#include <string>

namespace Calc {

class Var_table {
public:
  double get_value(const std::string&);
  void set_value(const std::string&, double);
  double define_name(const std::string&, double);

private:
  std::map<std::string, double> table;
  bool is_declared(const std::string&);
};
}

#endif


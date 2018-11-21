#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Calculator.h"

using std::cerr;
using std::cin;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;

int main()
{
  cout << "Please enter the name of the input files (end with EOF): ";
  vector<string> fnames;
  for (string fname; cin >> fname;) {
    fnames.push_back(fname);
  }

  for (const auto& fname : fnames) {
    ifstream ifs { fname };
    if (!ifs) {
      cerr << "cannot open file " + fname << '\n';
      continue; // skip the file and start with the next one
    }

    Calc::Calculator calc { ifs };

    try {
      calc.calculate();
    } catch (...) {
      cerr << "unknown error\n";
      return 2;
    }
  }

  return 0;
}


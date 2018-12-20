#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Punct_stream.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main()
{
  std::ifstream ifs { "input.txt" };
  Punct_stream ps { ifs };
  ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
  ps.case_sensitive(false);

  vector<string> vs;
  for (string word; ps >> word;) {
    if (!ps) {
    }
    vs.push_back(word);
  }

  std::sort(vs.begin(), vs.end());
  for (size_t i = 0; i < vs.size(); ++i) {
    if (i == 0 || vs[i] != vs[i - 1])
      cout << vs[i] << '\n';
  }
}

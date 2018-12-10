#include <algorithm>
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
  Punct_stream ps { cin };
  ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
  ps.case_sensitive(false);

  vector<string> vs;
  for (string word; ps >> word;) {
    vs.push_back(word);
  }

  std::sort(vs.begin(), vs.end());
  for (size_t i = 0; i < vs.size(); ++i) {
    if (i == 0 || vs[i] != vs[i - 1])
      cout << vs[i] << '\n';
  }
}

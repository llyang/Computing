#include <fstream>
#include <iostream>
#include <string>

#include "Punct_stream.h"

using std::cout;
using std::string;

int main()
{
  std::ifstream ifs { "test.csv" };
  Punct_stream ps { ifs };
  ps.whitespace(",");

  string id;
  int mid_score;
  int final_score;

  while (ps >> id >> mid_score >> final_score) {
    cout << id << '\t' << mid_score << '\t' << final_score << '\n';
  }
}

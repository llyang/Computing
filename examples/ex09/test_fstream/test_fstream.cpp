#include <cmath>
#include <fstream>
#include <iostream>

using std::cerr;
using std::ifstream;
using std::ofstream;
using std::string;

int main()
{
  ifstream ifs { "raw_scores.txt" };
  if (!ifs) {
    cerr << "cannot open file: raw_scores.txt for reading\n";
    return 1;
  }
  ofstream ofs { "total_scores.txt" };
  if (!ofs) {
    cerr << "cannot open file: final_scores.txt for writing\n";
    return 2;
  }
  while (ifs) {
    string id;
    int mid_score;
    int final_score;
    ifs >> id >> mid_score >> final_score;
    if (ifs) {
      int total_score { int(round(mid_score * 0.4 + final_score * 0.6)) };
      ofs << id << '\t' << total_score << '\n';
    }
  }
  return 0;
}

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cerr;
using std::cout;
using std::ifstream;
using std::istream;
using std::runtime_error;
using std::vector;

vector<int> read_vector(istream& ist, char terminator)
{
  vector<int> v;
  for (int i; ist >> i;)
    v.push_back(i);

  if (ist.bad()) {
    throw runtime_error { "这一定是机关的阴谋! El Psy Congroo!" };
  }

  if (ist.eof()) {
    return v;
  }

  if (ist.fail()) {
    ist.clear(); // 将状态设为good
    char c;
    ist >> c;
    if (c != terminator) {
      cerr << "error reading vector\n";
      ist.unget(); // 放回上一次读入的字符
      ist.clear(std::ios_base::failbit); // 将状态设为fail
    }
  }

  return v;
}

int main()
{
  ifstream ifs { "vectors.txt" };
  if (!ifs) {
    cerr << "cannot open file: vectors.txt for reading\n";
    return 1;
  }

  while (ifs) {
    vector<int> v { read_vector(ifs, '*') };
    if (ifs || !v.empty())
      cout << v.size() << '\n';
  }

  return 0;
}

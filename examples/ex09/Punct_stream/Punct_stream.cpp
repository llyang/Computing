#include <iostream>
#include <string>

#include "Punct_stream.h"

using std::string;

Punct_stream& Punct_stream::operator>>(string& s)
{
  while (!(buffer >> s)) {
    if (buffer.bad() || !source.good())
      return *this;
    buffer.clear();

    string line;
    getline(source, line);

    for (char& ch : line) {
      if (is_whitespace(ch))
        ch = ' ';
      else if (!sensitive)
        ch = tolower(ch);
    }

    buffer.str(line);
  }
  return *this;
}

Punct_stream& Punct_stream::operator>>(int& n)
{
  while (!(buffer >> n)) {
    if (buffer.bad() || !source.good())
      return *this;
    buffer.clear();

    string line;
    getline(source, line);

    for (char& ch : line) {
      if (is_whitespace(ch))
        ch = ' ';
      else if (!sensitive)
        ch = tolower(ch);
    }

    buffer.str(line);
  }
  return *this;
}

bool Punct_stream::is_whitespace(char c)
{
  for (char w : white) {
    // cppcheck-suppress useStlAlgorithm
    if (c == w)
      return true;
  }
  return false;
}

Punct_stream::operator bool() const
{
  return !(buffer.fail() || buffer.bad()) && source.good();
}


#ifndef _PUNCT_STREAM_H
#define _PUNCT_STREAM_H

#include <iostream>
#include <sstream>
#include <string>

class Punct_stream {
public:
  Punct_stream(std::istream& is)
      : source { is }
      , sensitive { true }
  {
  }

  void whitespace(const std::string& s) { white = s; }
  void add_white(char c) { white += c; }
  bool is_whitespace(char c);
  void case_sensitive(bool b) { sensitive = b; }
  bool is_case_sensitive() const { return sensitive; }

  Punct_stream& operator>>(std::string& s);
  Punct_stream& operator>>(int& n);
  explicit operator bool() const;

private:
  std::istream& source;
  std::istringstream buffer;
  std::string white;
  bool sensitive;
};

#endif

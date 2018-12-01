#ifndef _TOKEN_STREAM_H
#define _TOKEN_STREAM_H

#include <iostream>

#include "Token.h"

namespace Calc {

class Token_stream {
public:
  Token_stream(std::istream& is)
      : ist { is }
  {
  }

  Token get();
  void putback(Token t);
  void ignore(char c);

  explicit operator bool() const { return bool(ist); }

private:
  std::istream& ist;
  bool full { false };
  Token buffer;
};

}

#endif

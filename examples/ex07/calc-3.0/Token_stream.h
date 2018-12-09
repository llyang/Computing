#ifndef _TOKEN_STREAM_H
#define _TOKEN_STREAM_H

#include "Token.h"

namespace Calc {

class Token_stream {
public:
  Token_stream() {}
  Token get();
  void putback(Token t);
  void ignore(char c);

private:
  bool full { false };
  Token buffer;
};

}

#endif

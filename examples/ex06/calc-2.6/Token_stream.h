#ifndef _TOKEN_STREAM_H
#define _TOKEN_STREAM_H

#include "Token.h"

class Token_stream {
public:
  Token get();
  void putback(Token t);

private:
  bool full { false };
  Token buffer;
};

#endif

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#ifndef TOKENIZE_H
#define TOKENIZE_H

class PlusToken {
 public:
  bool operator==(const PlusToken&) const;
};

class MinusToken {
 public:
  bool operator==(const MinusToken&) const;
};

class MultiplyToken {
 public:
  bool operator==(const MultiplyToken&) const;
};

class DivideToken {
 public:
  bool operator==(const DivideToken&) const;
};

class ResidualToken {
 public:
  bool operator==(const ResidualToken&) const;
};

class OpeningBracketToken {
 public:
  bool operator==(const OpeningBracketToken&) const;
};

class ClosingBracketToken {
 public:
  bool operator==(const ClosingBracketToken&) const;
};

class SqrToken {
 public:
  bool operator==(const SqrToken&) const;
};

class MaxToken {
 public:
  bool operator==(const MaxToken&) const;
};

class MinToken {
 public:
  bool operator==(const MinToken&) const;
};

class AbsToken {
 public:
  bool operator==(const AbsToken&) const;
};

class NumberToken {
 public:
  explicit NumberToken(const int&);
  int value;
  bool operator==(const NumberToken&) const;
};

class UnknownToken {
 public:
  explicit UnknownToken(const std::string&);
  std::string value;
  bool operator==(const UnknownToken&) const;
};

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(std::string_view);

#endif

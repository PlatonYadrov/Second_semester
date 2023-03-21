#include "tokenize.h"
// #include <variant>

bool PlusToken::operator==(const PlusToken&) const {
  return true;
}

bool MinusToken::operator==(const MinusToken&) const {
  return true;
}

bool MultiplyToken::operator==(const MultiplyToken&) const {
  return true;
}

bool DivideToken::operator==(const DivideToken&) const {
  return true;
}

bool ResidualToken::operator==(const ResidualToken&) const {
  return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken&) const {
  return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken&) const {
  return true;
}

bool SqrToken::operator==(const SqrToken&) const {
  return true;
}

bool MaxToken::operator==(const MaxToken&) const {
  return true;
}

bool MinToken::operator==(const MinToken&) const {
  return true;
}

bool AbsToken::operator==(const AbsToken&) const {
  return true;
}

bool NumberToken::operator==(const NumberToken& other) const {
  return value == other.value;
}

NumberToken::NumberToken(const int& var) {
  value = var;
}

UnknownToken::UnknownToken(const std::string& var) {
  value = var;
}

bool UnknownToken::operator==(const UnknownToken& other) const {
  return value == other.value;
}

// using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
//                            ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(std::string_view s) {
  std::vector<std::string> tokenize;
  std::vector<Token> answer;
  std::string temp;
  Token t;
  if (!(s.empty())) {
    for (size_t i = 0; i < s.size(); ++i) {
      if ((s[i] == ' ') && !(temp.empty())) {
        tokenize.push_back(temp);
        temp = "";
      } else if (s[i] != ' ') {
        temp.push_back(s[i]);
      }
      if ((i == s.size() - 1) && (s[s.size() - 1] != ' ')) {
        tokenize.push_back(temp);
      }
    }
  }
  if (!(s.empty())) {
    for (const auto& tok : tokenize) {
      if (tok == "+") {
        t = PlusToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "-") {
        t = MinusToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "*") {
        t = MultiplyToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "/") {
        t = DivideToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "%") {
        t = ResidualToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "(") {
        t = OpeningBracketToken();
        answer.push_back(t);
        continue;
      }
      if (tok == ")") {
        t = ClosingBracketToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "sqr") {
        t = SqrToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "max") {
        t = MaxToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "min") {
        t = MinToken();
        answer.push_back(t);
        continue;
      }
      if (tok == "abs") {
        t = AbsToken();
        answer.push_back(t);
        continue;
      }
      bool all_numbers = true;
      int j = 0;
      for (const auto& element : tok) {
        if (j == 0) {
          ++j;
          if (!((element >= '0' && element <= '9') || element == '-' || element == '+')) {
            all_numbers = false;
          }
        } else {
          if (!(element >= '0' && element <= '9')) {
            all_numbers = false;
          }
        }
      }
      if (all_numbers) {
        // NumberToken t(0);
        // if (tok[0] == '-' || tok[0] == '+') {
        //   for (size_t i = 1; i < tok.size(); ++i) {
        //     t.value = 10 * (t.value) + static_cast<int>(tok[i] - '0');
        //   }
        //   if (tok[0] == '-') {
        //     t.value = 0 - t.value;
        //   }
        // } else {
        //   for (size_t i = 0; i < tok.size(); ++i) {
        //     t.value = 10 * (t.value) + static_cast<int>(tok[i] - '0');
        //   }
        // }
        // Token tok = t;
        // answer.push_back(tok);
        t = NumberToken(std::stoi(tok));
        answer.push_back(t);
      } else {
        t = UnknownToken(tok);
        answer.push_back(t);
      }
    }
  }
  return answer;
}

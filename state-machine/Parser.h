//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H

#include "states/Base.h"
#include "Token.h"
#include "State.h"

#include <string>

class Parser {
 public:
  Stack stack_;
  explicit Parser();
  void ParseString(const std::string &code);

 private:
  State *current_state_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H

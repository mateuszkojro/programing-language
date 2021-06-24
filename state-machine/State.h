//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H

#include <deque>
#include "Token.h"
#include "../Stack.h"
#include <iostream>

#define CHANGE_STATE(state) std::clog << std::endl << state << std::endl;

class State {
 public:
  explicit State(Stack &stack) : stack_(stack) {}
  virtual State *Parse(const std::string &text, int position) = 0;

 protected:
  Stack &stack_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H

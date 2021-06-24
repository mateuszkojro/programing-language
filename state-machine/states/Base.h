//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H

#include "State.h"
class Base : public State {
  std::string buffer;
 public:
  explicit Base(Stack &stack);

  State *Parse(const std::string &text, int position) override;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H

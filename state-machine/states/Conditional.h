//
// Created by mateu on 6/5/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H

#include <Token.h>
#include "State.h"
#include "Variable.h"
#include "VariableAssigment.h"
#include "../Matrix.h"
#include "../Utility.h"

class Conditional : public State {

  VariableAssigment *condition_parser_;
  Variable *condition_;

 public:

  explicit Conditional(Stack &stack);

  State *Parse(const std::string &text, int position) override;

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H

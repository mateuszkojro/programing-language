//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_CONDITIONAL_H_
#define INTERPRETER_LANGUAGE_CONDITIONAL_H_

#include "Block.h"
#include "IStatment.h"

class Conditional : public IStatment {
 public:
  Conditional(IStatment *condition, Block *true_Case, Block *false_case);

  IValue *eval(Env &env) override;

  static std::optional<std::pair<IStatment *, std::string>> parse(const std::string &text);

 private:
  IStatment *condition_;
  Block *true_case_;
  Block *false_case_;
};

#endif//INTERPRETER_LANGUAGE_CONDITIONAL_H_

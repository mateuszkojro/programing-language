//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_LOOP_H_
#define INTERPRETER_LANGUAGE_LOOP_H_

#include "Block.h"
#include "IStatment.h"

class Loop : public IStatment {
 public:
  static std::optional<std::pair<IStatment *, std::string>> parse(const std::string &text);
  Loop(IStatment *condition, Block *bloc);
  IValue *eval(Env &env);

 private:
  IStatment *condition_;
  Block *block_;
};

#endif//INTERPRETER_LANGUAGE_LOOP_H_

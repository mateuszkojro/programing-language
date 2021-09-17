//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_FUNCCALL_H_
#define INTERPRETER_LANGUAGE_FUNCCALL_H_

#include "IStatment.h"
#include <vector>

class FuncCall : public IStatment {
 public:
  static std::optional<std::pair<FuncCall *, std::string>> parse(const std::string &text);
  IValue *eval(Env &env) override;

  FuncCall(std::string func_name, std::vector<IStatment *> passed_names);

 private:
  std::string func_name_;
  std::vector<IStatment *> args_;
};

#endif//INTERPRETER_LANGUAGE_FUNCCALL_H_

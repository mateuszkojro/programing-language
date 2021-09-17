//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_FUNCDEF_H_
#define INTERPRETER_LANGUAGE_FUNCDEF_H_

#include <utility>

#include "Block.h"
#include "IStatment.h"

class FuncDef : public IStatment {
 public:
  static std::optional<std::pair<FuncDef *, std::string>> parse(const std::string &text);

  FuncDef() = default;
  FuncDef(std::string func_name, std::vector<std::string> args, Block *body) : name_(std::move(func_name)),
																			   body_(body), args_(std::move(args)) {}

  IValue *eval(Env &env) override;

  std::vector<std::string> get_arg_names() { return args_; }
  Block *get_func_body() { return body_; }

 private:
  std::string name_;
  std::vector<std::string> args_;
  Block *body_;
};

#endif//INTERPRETER_LANGUAGE_FUNCDEF_H_

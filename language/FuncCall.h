//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_FUNCCALL_H_
#define INTERPRETER_LANGUAGE_FUNCCALL_H_

#include "IStatment.h"
#include <vector>

/**
 * @brief
 */
class FuncCall : public IStatment {
 public:
  static std::optional<std::pair<FuncCall *, std::string>> parse(const std::string &text);

  FuncCall(std::string func_name, std::vector<IStatment *> passed_names);

  /**
   * @brief Function will be called with the argument passed
   * @param env Outer scope
   * @return Value returned from the function
   */
  IValue *eval(Env &env) override;

  virtual ~FuncCall();

 private:
  /**
   * @brief Name of a function to be called
   */
  std::string func_name_;

  /**
   * @brief Statment that will be evaluated and passed to a function
   */
  std::vector<IStatment *> args_;
};

#endif//INTERPRETER_LANGUAGE_FUNCCALL_H_

#ifndef INTERPRETER_LANGUAGE_CONDITIONAL_H_
#define INTERPRETER_LANGUAGE_CONDITIONAL_H_

#include "Block.h"
#include "IStatment.h"

/**
 * @brief
 */
class Conditional : public IStatment {
 public:
  static std::optional<std::pair<IStatment *, std::string>> parse(const std::string &text);

  Conditional(IStatment *condition, Block *true_Case, Block *false_case);

  /**
   * @brief
   * @param env
   * @return
   */
  IValue *eval(Env &env) override;


 private:
  /**
   * @brief
   */
  IStatment *condition_;
  /**
   * @brief
   */
  Block *true_case_;
  /**
   * @brief
   */
  Block *false_case_;
};

#endif//INTERPRETER_LANGUAGE_CONDITIONAL_H_

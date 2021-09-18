#ifndef INTERPRETER_LANGUAGE_CONDITIONAL_H_
#define INTERPRETER_LANGUAGE_CONDITIONAL_H_

#include "Block.h"
#include "IStatment.h"

/**
 * @brief Conditional statments (if, else statments)
 * @warning Every value other than NaN, 0, and Null is positive
 * @details Can be used in assigment operations then the block will be evaluated
 * the standard way
 */
class Conditional : public IStatment {
 public:
  static std::optional<std::pair<IStatment *, std::string>> parse(
	  const std::string &text);

  Conditional(IStatment *condition, Block *true_Case, Block *false_case);

  /**
   * @brief Evaluates all the statments in either true or false block
   * depending on evaluation of condition (all in passed scope) and returns the
   * last statment in corresponding block
   * @param env Scope
   * @return Evaluation of the last statment in one of the paths or Null if the
   * path does not exist
   */
  IValue *eval(Env &env) override;

  virtual ~Conditional();

 private:
  /**
   * @brief Condition on wich depends the choice of the path (every value other
   * than NaN, 0, and Null is positive)
   */
  IStatment *condition_;
  /**
   * @brief Block that will be evaluated if the condition is positive
   */
  Block *true_case_;
  /**
   * @brief Block that will be evaluated if the condition is not positive
   */
  Block *false_case_;
};

#endif// INTERPRETER_LANGUAGE_CONDITIONAL_H_

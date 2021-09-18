#ifndef INTERPRETER_LANGUAGE_ERRORSTATMENT_H_
#define INTERPRETER_LANGUAGE_ERRORSTATMENT_H_

#include <utility>

#include "IStatment.h"
#include "IValue.h"
#include "utils.h"

/**
 * @brief Error value created when there is an error while evaluation
 */
class ErrorStatment : public IStatment, public IValue {
 public:
  explicit ErrorStatment(std::string error)
	  : IValue(IValue::Type::Error), error_message_(std::move(error)) {}

  /**
   * @brief Evaluation of the Error returns itself
   * @param env Enviroment is ignored while evaluation
   * @return Itself
   */
  IValue* eval(Env& env) override;

  /**
   * @brief Value of error is NaN
   * @return NaN
   */
  double value() const override;

  /**
   * @brief Geter for error message
   * @return Error message
   */
  std::string error();

 private:
  /**
   * @brief Error message describing what happened
   */
  std::string error_message_;
};

#endif// INTERPRETER_LANGUAGE_ERRORSTATMENT_H_

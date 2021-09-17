#ifndef INTERPRETER_LANGUAGE_ERRORSTATMENT_H_
#define INTERPRETER_LANGUAGE_ERRORSTATMENT_H_

#include <utility>

#include "IStatment.h"
#include "IValue.h"

class ErrorStatment : public IStatment, public IValue {
 public:
  ErrorStatment(std::string error) : IValue(IValue::Type::Error), error_message_(std::move(error)) {}

  IValue *eval(Env &env) override;
  double value() const override;

  std::string error();

 private:
  std::string error_message_;
};

#endif//INTERPRETER_LANGUAGE_ERRORSTATMENT_H_

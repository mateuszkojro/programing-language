#include "ErrorStatment.h"

#include <cmath>

IValue* ErrorStatment::eval(Env& env) { return this; }

double ErrorStatment::value() const {
  FIXME("Error is implicitly converted to NaN here");
  return NAN;
}

std::string ErrorStatment::error() { return error_message_; }

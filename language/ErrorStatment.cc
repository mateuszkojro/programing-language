#include "ErrorStatment.h"

#include <cmath>

IValue* ErrorStatment::eval(Env& env) { return new ErrorStatment(*this); }

double ErrorStatment::value() const {
  FIXME("Error is implicitly converted to NaN here");
  return NAN;
}

std::string ErrorStatment::error() { return error_message_; }

ErrorStatment* ErrorStatment::clone() { return new ErrorStatment(*this); }

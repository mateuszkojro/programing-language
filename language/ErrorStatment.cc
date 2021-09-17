//
// Created by mateu on 9/17/2021.
//

#include "ErrorStatment.h"
#include <cassert>
IValue *ErrorStatment::eval(Env &env) {
  return this;
}
double ErrorStatment::value() const {
  assert(false && "Trying to extract value from the error");
  return NAN;
}
std::string ErrorStatment::error() {
  return error_message_;
}

#ifndef STATMENT_H
#define STATMENT_H

#include <optional>
#include <string>

#include "env.h"

using std::optional;
using std::pair;
using std::string;

class IStatment {
 public:
  static optional<pair<IStatment *, string>> parse(const string &text);
  IStatment() = default;

  virtual IValue *eval(Env &env) = 0;

  virtual ~IStatment() = default;
};

#endif
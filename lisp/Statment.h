#ifndef STATMENT_H
#define STATMENT_H

#include <optional>
#include <string>

#include "env.h"

using std::optional;
using std::pair;
using std::string;

class Statment {
public:
  static optional<pair<Statment *, string>> parse(const string &text);
  Statment() = default;

  virtual Value* eval(Env& env) = 0;

  virtual ~Statment() = default;
};

#endif
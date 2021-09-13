#include "IValue.h"
#include <optional>
#include <string>
#include <unordered_map>

#ifndef ENV_H
#define ENV_H

using std::string;
using std::optional;

class Env {
public:
  void store_binding(const string &name, IValue *val);
  optional<IValue *> get_binding_value(const string& name);

private:
  std::unordered_map<string, IValue *> bindings_;
};

#endif

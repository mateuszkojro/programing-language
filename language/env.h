#include "Value.h"
#include <unordered_map>
#include <string>
#include <optional>

#ifndef ENV_H
#define ENV_H

using std::string;
using std::optional;

class Env {
public:
  void store_binding(const string &name, Value *val);
  optional<Value*> get_binding_value(const string& name);

private:
  std::unordered_map<string, Value *> bindings_;
};

#endif

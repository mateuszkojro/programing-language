#include "IValue.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#ifndef ENV_H
#define ENV_H

using std::optional;
using std::string;

class Env {
 public:
  void store_binding(const string &name, std::unique_ptr<IValue> val);
  optional<std::unique_ptr<IValue>> get_binding_value(const string &name);

 private:
  std::unordered_map<string, std::unique_ptr<IValue>> bindings_;
};

#endif

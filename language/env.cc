#include "env.h"
#include <string>

void Env::store_binding(const string &name, Value *val) {
  bindings_[name] = val;
}

optional<Value *> Env::get_binding_value(const string &name) {
  // There is no value with that name
  if (bindings_.find(name) == bindings_.end())
    return std::nullopt;
  return bindings_[name];
}

#include "env.h"
#include <cassert>
#include <string>

void Env::store_binding(const string &name, std::unique_ptr<IValue> val) {
  bindings_[name] = std::move(val);
}

optional<std::unique_ptr<IValue>> Env::get_binding_value(const string &name) {
//  assert(false && "Fixme unique ptr cannot be copied");
  // There is no value with that name
  if (bindings_.find(name) == bindings_.end())
	return std::nullopt;
  auto &binding = bindings_[name];
  return std::make_optional(std::make_unique<IValue>(*binding));
}

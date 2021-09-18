#include "env.h"

#include <string>

#include "utils.h"

void Env::store_binding(const string& name, IValue* val) {
  bindings_[name] = val;
}

optional<IValue*> Env::get_binding_value(const string& name) {
  // There is no value with that name
  if (bindings_.find(name) == bindings_.end())
	return std::nullopt;
  return bindings_[name];
}

void Env::store_function(const string& name, FuncDef* val) {
  functions_[name] = val;
}

optional<FuncDef*> Env::get_function_def(const string& name) {
  // There is no value with that name
  if (functions_.find(name) == functions_.end())
	return std::nullopt;
  return functions_[name];
}

Env::~Env() {
  FIXME(
	  "There is a memory leak here that is being solved in next version using "
	  "shared ptrs");
  //  for (auto [key, value] : bindings_) {
  //	delete value;
  //  }
  //  for (auto [key, value] : functions_) {
  //	delete value;
  //  }
}

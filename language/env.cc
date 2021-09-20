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

/**
 * @warning Memory leak - not implemented garbage collector
 * @details
 * Here is the place where language memory management needs to be considered
 * there are basically two options:
 *
 * - Leave the memory management to the user
 * - Implement some kind of garbage collection
 * Given the fact that the language needs a runtime to execute scripts
 * I decided on implementing the garbage collector using method of reference
 * counting. Unfortunately time for finishing this assigment run out so for now
 * unfortunately this place leaks memory.
 *
 * Possible implementation of reference counted GC should be based on
 * std::shared_ptr for simplicity of implementation and performance benefits
 * that stand from using STL implementation
 */
Env::~Env() {
  //    for (auto [key, value] : bindings_) { delete value; }
  //    for (auto [key, value] : functions_) { delete value; }
}

Env::Env(const Env& other) {
  for (auto [key, value] : other.bindings_) { bindings_[key] = value->clone(); }
  for (auto [key, value] : other.functions_) {
	functions_[key] = value->clone();
  }
}

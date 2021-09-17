#include "IStatment.h"
#include "IValue.h"
#include <optional>
#include <string>
#include <unordered_map>

#ifndef ENV_H
#define ENV_H

using std::optional;
using std::string;

class FuncDef;

class Env {
 public:
  void store_binding(const string &name, IValue *val);
  void store_function(const string &name, FuncDef *val);
  //  void store_definition(const string &name, IStatment *val);
  optional<IValue *> get_binding_value(const string &name);
  optional<FuncDef *> get_function_def(const string &name);

  std::unordered_map<string, IValue *> &get_bindings() { return bindings_; };

 private:
  std::unordered_map<string, IValue *> bindings_;
  std::unordered_map<string, FuncDef *> functions_;
};

#endif

#ifndef BINDING_USAGE_H
#define BINDING_USAGE_H

#include "utils.h"
#include <string>
#include <utility>
#include "env.h"

using std::pair;
using std::string;

class BindingUsage {
public:
  BindingUsage(const string &name);
  ~BindingUsage() = default;

  static optional<pair<BindingUsage, string>> parse(string text);
  bool operator==(const BindingUsage& other) const;

  optional<Value*> eval(Env& env);

private:
  string name_;
};

#endif
#ifndef BINDING_USAGE_H
#define BINDING_USAGE_H

#include "IStatment.h"
#include "env.h"
#include "utils.h"
#include <string>
#include <utility>

using std::pair;
using std::string;

class BindingUsage : public IStatment {
 public:
  BindingUsage(const string &name);
  BindingUsage(const string &name, IStatment *new_value);

  ~BindingUsage() = default;

  static optional<pair<BindingUsage *, string>> parse(const string &text);
  bool operator==(const BindingUsage &other) const;

  IValue *eval(Env &env) override;

 private:
  string name_;
  IStatment *new_value_ = nullptr;
};

#endif
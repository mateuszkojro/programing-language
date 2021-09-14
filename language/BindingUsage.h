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
  BindingUsage(string name);
  ~BindingUsage() = default;

  static optional<pair<BindingUsage *, string>> parse(string text);
  bool operator==(const BindingUsage &other) const;

  std::unique_ptr<IValue> eval(Env &env) override;

 private:
  string name_;
};

#endif
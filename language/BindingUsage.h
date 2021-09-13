#ifndef BINDING_USAGE_H
#define BINDING_USAGE_H

#include "Statment.h"
#include "utils.h"
#include <string>
#include <utility>
#include "env.h"

using std::pair;
using std::string;

class BindingUsage : public Statment {
public:
  BindingUsage(const string &name);
  ~BindingUsage() = default;

  static optional<pair<BindingUsage*, string>> parse(string text);
  bool operator==(const BindingUsage& other) const;

  Value* eval(Env& env) override;

private:
  string name_;
};

#endif
#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>

#include "Expr.h"

using std::optional;
using std::string;

class BindDef : public Statment {
public:
  static optional<pair<BindDef, string>> Parse(const string &text);

  BindDef(const string &name, Expr *expr);

  Value* eval(Env &env) override;

  bool operator==(const BindDef &op) const;

private:
  string name_;
  Expr *expr_;
};

#endif

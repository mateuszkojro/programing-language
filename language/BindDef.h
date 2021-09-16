#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>

#include "Expr.h"

using std::optional;
using std::string;

class BindDef : public IStatment {
 public:
  static optional<pair<BindDef, string>> parse(const string &text);

  BindDef(const string &name, IExpr *expr);

  IValue *eval(Env &env) override;

  bool operator==(const BindDef &op) const;

 private:
  string name_;
  IExpr *expr_;
};

#endif

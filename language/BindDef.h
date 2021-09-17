#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>
#include <utility>

#include "Expr.h"

using std::optional;
using std::string;

class BindDef : public IStatment {
 public:
  static optional<pair<BindDef, string>> parse(const string &text);

  BindDef() = delete;
  BindDef(string name, IExpr *expr);
  ~BindDef() override = default;

  bool operator==(const BindDef &op) const;

  IValue *eval(Env &env) override;

 private:
  string name_;
  IExpr *expr_;
};

#endif

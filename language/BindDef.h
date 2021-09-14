#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>
#include <memory>

#include "Expr.h"

using std::optional;
using std::string;

class BindDef : public IStatment {
 public:
  static optional<pair<BindDef, string>> parse(const string &text);

  BindDef(string name, IExpr *expr);

  std::unique_ptr<IValue> eval(Env &env) override;

  bool operator==(const BindDef &op) const;

 private:
  string name_;
  IExpr *expr_;
};

#endif

#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>

#include "Expr.h"

using std::string;
using std::optional;

class BindDef {
public:
  static optional<pair<BindDef, string>> Parse(const string &text);

  BindDef(const string &name, Expr* expr);

  void eval(Env &env);

  bool operator==(const BindDef &op) const;

private:
  string name_;
  Expr* expr_;
};


#endif

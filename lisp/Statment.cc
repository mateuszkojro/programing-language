#include "Statment.h"
#include "BindDef.h"

optional<pair<Statment *, string>> Statment::parse(const string &text) {

  auto parse_binding = BindDef::Parse(text);
  if (parse_binding) {
    auto result = parse_binding.value();
    return pair(new BindDef(result.first), result.second);
  }

  auto parse_expr = Expr::Parse(text);
  if (parse_expr) {
    return parse_expr.value();
  }

  return nullopt;
}

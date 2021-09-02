#include "Statment.h"
#include "BindDef.h"
#include "BindingUsage.h"

optional<pair<Statment *, string>> Statment::parse(const string &text) {

  auto parse_binding = BindDef::Parse(text);
  if (parse_binding) {
    auto result = parse_binding.value();
    return pair(new BindDef(result.first), result.second);
  }

  auto parse_expr = Expr::Parse(text);
  if (parse_expr) {
    return parse_expr;
  }

  auto parse_binding_usage = BindingUsage::parse(text);
  if (parse_binding_usage){
    return parse_binding_usage;
  }

  return nullopt;
}

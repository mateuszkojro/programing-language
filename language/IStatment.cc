#include "IStatment.h"
#include "BindDef.h"
#include "BindingUsage.h"
#include "Block.h"

optional<pair<IStatment *, string>> IStatment::parse(const string &text) {

  auto parse_binding = BindDef::parse(text);
  if (parse_binding) {
	auto result = parse_binding.value();
	return pair(new BindDef(result.first), result.second);
  }

  auto parse_expr = IExpr::parse(text);
  if (parse_expr) {
	return parse_expr;
  }

  auto parse_binding_usage = BindingUsage::parse(text);
  if (parse_binding_usage) {
	return parse_binding_usage;
  }

  auto parse_block = Block::parse(text);
  if (parse_block) { return parse_block; }

  return nullopt;
}

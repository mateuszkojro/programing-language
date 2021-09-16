#include "IStatment.h"
#include "BindDef.h"
#include "BindingUsage.h"
#include "Block.h"
#include "FuncCall.h"
#include "FuncDef.h"

optional<pair<IStatment *, string>> IStatment::parse(const string &text) {

  auto str = extract_whitespace(text).second;

  auto parse_binding = BindDef::parse(str);
  if (parse_binding) {
	auto result = parse_binding.value();
	return pair(new BindDef(result.first), result.second);
  }

  auto parse_func_call = FuncCall::parse(str);
  if (parse_func_call) { return parse_func_call; }

  auto parse_func_def = FuncDef::parse(str);
  if (parse_func_def) { return parse_func_def; }

  auto parse_expr = IExpr::parse(str);
  if (parse_expr) {
	return parse_expr;
  }

  auto parse_binding_usage = BindingUsage::parse(str);
  if (parse_binding_usage) {
	return parse_binding_usage;
  }

  auto parse_block = Block::parse(str);
  if (parse_block) { return parse_block; }


  return nullopt;
}

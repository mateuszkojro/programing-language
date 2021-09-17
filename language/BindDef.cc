#include "BindDef.h"
#include <utility>

optional<pair<BindDef, string>> BindDef::parse(const string &text) {

  // Variiable declaration needs to start with "mat"
  auto tag1 = tag(text, "mat");
  if (!tag1)
	return nullopt;

  auto str = tag1.value().second;

  // Remove following whitespace
  auto whitespace1 = extract_whitespace(str);
  // There needs to be a space between "mat" and var name
  if (whitespace1.first == "")
	return nullopt;
  str = whitespace1.second;

  // Extract the name of the variable
  auto name_parse = extract_identifier(str);
  if (!name_parse)
	return nullopt;

  str = name_parse.value().second;

  // Save name of the var for later
  auto bind_name = name_parse.value().first;

  str = extract_whitespace(str).second;

  // Now there needs to be a "="
  auto tag2 = tag(str, "=");
  if (!tag2)
	return nullopt;

  str = tag2.value().second;

  str = extract_whitespace(str).second;

  // Parse an expresion that should be assigned to var
  auto expr_parse = IExpr::parse(str);
  if (!expr_parse)
	return nullopt;

  IExpr *bind_expr = expr_parse.value().first;

  // Create var
  return optional(
	  std::make_pair(BindDef(bind_name, bind_expr), expr_parse.value().second));
}

BindDef::BindDef(const std::string &name, IExpr *expr)
	: name_(name), expr_(expr) {}

bool BindDef::operator==(const BindDef &other) const {
  std::cout << "Thats a problem" << std::endl;
  return name_ == other.name_;
  // &&
  //        ((Number *)expr_ ==
  //            ((Number *)other.expr_);
}

IValue *BindDef::eval(Env &env) {
  auto result = this->expr_->eval(env);
  env.store_binding(name_, result);
  return result;
}

#include "BindDef.h"
#include <utility>
#include <cmath>

optional<pair<BindDef, string>> BindDef::parse(const string &text) {

  // Variiable declaration needs to start with "mat"
  auto tag1 = tag(text, "mat");
  if (!tag1)
	  return nullopt;

  auto str = tag1->second;

  // Remove following whitespace
  auto whitespace1 = extract_whitespace(str);
  // There needs to be a space between "mat" and var name
  if (whitespace1.first.empty())
	  return nullopt;
  str = whitespace1.second;

  // Extract the name of the variable
  auto name_parse = extract_identifier(str);
  if (!name_parse)
	  return nullopt;

  str = name_parse.value().second;

  // Save name of the var for later
  auto bind_name = name_parse->first;

  str = extract_whitespace(str).second;

  // Now there needs to be a "="
  auto tag2 = tag(str, "=");
  if (!tag2)
	  return std::make_pair(BindDef(bind_name,new ExprNumber(Number(NAN))), str);

  str = tag2->second;

  str = extract_whitespace(str).second;

  // Parse an expresion that should be assigned to var
  auto expr_parse = IExpr::parse(str);
  if (!expr_parse)
	  return nullopt;

  IExpr *bind_expr = expr_parse->first;

  // Create var
  return std::make_pair(BindDef(bind_name, bind_expr), expr_parse->second);
}

BindDef::BindDef(std::string name, IExpr *expr)
	: name_(std::move(name)), expr_(expr) {}

bool BindDef::operator==(const BindDef &other) const {
  FIXME("Comparing variables with just the name");
  return name_ == other.name_;
}

IValue *BindDef::eval(Env &env) {
  // We need to eval variable in current contex
  auto result = this->expr_->eval(env);
  // And assign ist value
  env.store_binding(name_, result);
  return result;
}

#include "BindingUsage.h"

#include "ErrorStatment.h"
#include "Null.h"
#include "env.h"
#include "utils.h"

BindingUsage::BindingUsage(string name) : name_(std::move(name)) {}

optional<pair<BindingUsage *, string>> BindingUsage::parse(const string &text) {
  auto parse_name = extract_identifier(text);
  if (!parse_name)
	return nullopt;

  auto str = parse_name->second;

  str = extract_whitespace(str).second;

  auto tag_extract = tag(str, "=");
  if (!tag_extract)
	return std::make_pair(new BindingUsage(parse_name->first), str);

  str = tag_extract->second;
  str = extract_whitespace(str).second;

  auto parseed_statment = IStatment::parse(str);
  if (!parseed_statment)
	return std::nullopt;

  str = parseed_statment->second;

  return std::make_pair(
	  new BindingUsage(parse_name->first, parseed_statment->first), str);
}
bool BindingUsage::operator==(const BindingUsage &other) const {
  return name_ == other.name_;
}
IValue *BindingUsage::eval(Env &env) {

  auto bind_val = env.get_binding_value(name_);
  if (!bind_val)
	return new ErrorStatment("Variable does not exist: " + name_);

  if (!new_value_)
	return bind_val.value();

  auto new_eval = new_value_->eval(env);
  env.store_binding(name_, new_eval);

  return new_eval;
}
BindingUsage::BindingUsage(string name, IStatment *new_value)
	: name_(std::move(name)), new_value_(new_value) {}

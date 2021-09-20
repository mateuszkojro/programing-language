#include "FuncCall.h"

#include <utility>

#include "ErrorStatment.h"
#include "FuncDef.h"
#include "Null.h"

IValue* FuncCall::eval(Env& env) {
  auto function = env.get_function_def(func_name_);
  if (!function)
	return new ErrorStatment("Function does not exit: " + func_name_);

  Env inner_scope(env);
  auto inner_names = function.value()->get_arg_names();

  if (inner_names.size() != args_.size())
	return new ErrorStatment("Number of passed arguments: "
							 + std::to_string(args_.size())
							 + " is not equal to number of expected arguments: "
							 + std::to_string(inner_names.size()));

  for (int i = 0; i < args_.size(); i++) {
	inner_scope.store_binding(inner_names[i], args_[i]->eval(env));
  }
  return function.value()->get_func_body()->eval(inner_scope)->clone();
}
std::optional<std::pair<FuncCall*, std::string>> FuncCall::parse(
	const string& text) {
  auto str = extract_whitespace(text).second;

  auto extracted_name = extract_identifier(text);
  if (!extracted_name)
	return std::nullopt;

  str = extracted_name->second;

  str = extract_whitespace(str).second;

  auto extract_open_tag = tag(str, "(");
  if (!extract_open_tag) {
	return std::nullopt;
  }
  str = extract_open_tag->second;
  str = extract_whitespace(str).second;

  vector<IStatment*> args;

  auto parse_statment = IStatment::parse(str);
  while (parse_statment) {

	str = parse_statment.value().second;

	args.push_back(parse_statment.value().first);

	str = extract_whitespace(str).second;

	parse_statment = IStatment::parse(str);
  }

  auto extract_close_tag = tag(str, ")");
  if (!extract_close_tag) {
	return std::nullopt;
  }
  str = extract_close_tag->second;
  str = extract_whitespace(str).second;

  return std::make_pair(new FuncCall(extracted_name->first, args), str);
}
FuncCall::FuncCall(std::string func_name, std::vector<IStatment*> args)
	: func_name_(std::move(func_name)), args_(std::move(args)) {}
FuncCall::~FuncCall() {
  for (auto statment : this->args_) { delete statment; }
}
FuncCall* FuncCall::clone() { return new FuncCall(*this); }

#include "FuncDef.h"
#include "Null.h"
#include "utils.h"
#include <optional>

std::optional<std::pair<FuncDef *, std::string>> FuncDef::parse(const string &text) {
  auto str = extract_whitespace(text).second;

  auto maybe_fn = tag(str, "fn");

  if (!maybe_fn)
	return std::nullopt;

  str = maybe_fn->second;
  str = extract_whitespace(str).second;

  auto extract_func_name = extract_identifier(str);
  if (!extract_func_name) {
	return std::nullopt;
  }
  str = extract_func_name->second;
  str = extract_whitespace(str).second;

  auto extract_open_tag = tag(str, "(");
  if (!extract_open_tag) {
	return std::nullopt;
  }
  str = extract_open_tag->second;
  str = extract_whitespace(str).second;

  std::vector<std::string> arg_names;
  auto arg_name = extract_identifier(str);
  while (arg_name) {
	arg_names.push_back(arg_name->first);
	str = arg_name->second;
	str = extract_whitespace(str).second;
	arg_name = extract_identifier(str);
  }

  auto extract_close_tag = tag(str, ")");
  if (!extract_close_tag) {
	return std::nullopt;
  }
  str = extract_close_tag->second;
  str = extract_whitespace(str).second;

  auto extract_func_body = Block::parse(str);
  if (!extract_func_body) {
	return std::nullopt;
  }
  str = extract_func_body->second;
  return std::make_pair(new FuncDef(extract_func_name->first, arg_names, extract_func_body->first), str);
}

IValue *FuncDef::eval(Env &env) {
  env.store_function(name_, this);
  return new class Null;
}

FuncDef::~FuncDef() {
  delete this->body_;
}

//
// Created by mateu on 9/16/2021.
//

#include "Loop.h"
#include "Null.h"
#include "utils.h"

std::optional<std::pair<IStatment *, std::string>> Loop::parse(const string &text) {
  auto str = extract_whitespace(text).second;

  auto extracted_tag = tag(str, "while");
  if (!extracted_tag)
	return std::nullopt;

  str = extracted_tag->second;
  str = extract_whitespace(str).second;

  auto extracted_paren = tag(str, "(");
  if (!extracted_paren)
	return std::nullopt;

  str = extracted_paren->second;
  str = extract_whitespace(str).second;

  auto condition = IStatment::parse(str);
  if (!condition)
	return std::nullopt;

  str = condition->second;
  str = extract_whitespace(str).second;

  auto extracted_paren_close = tag(str, ")");
  if (!extracted_paren_close)
	return std::nullopt;

  str = extracted_paren_close->second;
  str = extract_whitespace(str).second;

  auto true_block = Block::parse(str);
  if (!true_block)
	return std::nullopt;

  str = true_block->second;
  str = extract_whitespace(str).second;

  return std::make_pair(new Loop(condition->first, true_block->first), str);
}
Loop::Loop(IStatment *condition, Block *block) : condition_(condition), block_(block) {}

IValue *Loop::eval(Env &env) {
  IValue *condition = condition_->eval(env);
  IValue *result_value = nullptr;
  while (!(condition->get_type() == IValue::Type::Null) && !(condition->value() == 0)) {
	result_value = block_->eval(env);// TODO memory leak
	condition = condition_->eval(env);
  }

  return result_value ? result_value : new Null;
}

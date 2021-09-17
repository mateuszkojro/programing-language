//
// Created by mateu on 9/16/2021.
//

#include "Conditional.h"
#include "Null.h"
#include "utils.h"

Conditional::Conditional(IStatment *condition, Block *true_Case, Block *false_case)
	: condition_(condition),
	  true_case_(true_Case),
	  false_case_(false_case) {}

std::optional<std::pair<IStatment *, std::string>> Conditional::parse(const string &text) {
  auto str = extract_whitespace(text).second;

  auto extracted_tag = tag(str, "if");
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

  auto extracted_else = tag(str, "else");
  if (!extracted_else)
	return std::make_pair(new Conditional(condition->first, true_block->first, nullptr), str);

  str = extracted_else->second;
  str = extract_whitespace(str).second;

  auto false_block = Block::parse(str);
  if (!false_block)
	return std::nullopt;

  str = false_block->second;
  str = extract_whitespace(str).second;

  return std::make_pair(new Conditional(condition->first, true_block->first, false_block->first), str);
}
IValue *Conditional::eval(Env &env) {
  auto condition = condition_->eval(env);

  if (condition->get_type() == IValue::Type::Null)
	return false_case_ ? false_case_->eval(env) : new Null;

  if (compare_double(condition->value(), 0))
	return false_case_ ? false_case_->eval(env) : new Null;

  if (condition->value() == NAN)
	return false_case_ ? false_case_->eval(env) : new Null;

  return true_case_->eval(env);
}

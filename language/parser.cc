#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include "Null.h"
#include "env.h"
#include "parser.h"

Number::Number(double number) : IValue(IValue::Number), value_(number) {}
optional<pair<Number, string>> Number::Parse(string number) {

//  std::cout << "Depreciated: should call lowercase parse" << std::endl;

  auto result = extract_digits(number);
  if (result.first.empty())
	return nullopt;

  try {
	return std::make_pair(Number(std::stod(result.first)), result.second);
  } catch (const std::invalid_argument &e) {
	std::cerr << "Malformed number: " << result.first << std::endl;
	return nullopt;
  } catch (const std::out_of_range &e) {
	std::cerr << "Number too large" << std::endl;
	return nullopt;
  }
}

optional<pair<Number *, string>> Number::parse(string number) {
  if (auto parsed_number = Parse(number))
	return std::make_pair(new Number(parsed_number->first),parsed_number->second);
  return std::nullopt;
}


double Number::value() const { return value_; }

bool Number::operator==(const Number &other) const {
  return this->value_ == other.value_;
}
bool Number::operator!=(const Number &other) const {
  return this->value_ != other.value_;
}

std::ostream &operator<<(std::ostream &os, const Number &n) {
  os << "Number(" << n.value_ << ")";
  return os;
}

Operator::Operator(Type t) { value_ = t; }

Operator::Type Operator::type() { return this->value_; }

optional<std::pair<Operator, string>> Operator::Parse(const string &expr) {

  auto result = extract_operator(expr);

  if (!result)
	return nullopt;
  auto &op = result.value().first;

  if (op == "+")
	return std::make_pair(Operator(Type::Add), result.value().second);
  else if (op == "-")
	return std::make_pair(Operator(Type::Subtract), result.value().second);
  else if (op == "*")
	return std::make_pair(Operator(Type::Multiply), result.value().second);
  else if (op == "/")
	return std::make_pair(Operator(Type::Divide), result.value().second);

  else
	return nullopt;
}

bool Operator::operator==(const Operator &other) const {
  return this->value_ == other.value_;
}
bool Operator::operator==(const Operator::Type &other) const {
  return this->value_ == other;
}

std::ostream &operator<<(std::ostream &os, const Operator &n) {
  os << "Number(" << n.value_ << ")";
  return os;
}
Parser::Parser() {
  environment_ = Env();
}
int Parser::parse(const string &code) {

  if (auto result = IStatment::parse(code)) {
	auto evaluated = result->first->eval(environment_);
	switch (evaluated->get_type()) {
	  case IValue::Number:
		std::cout << *(Number *)evaluated << std::endl;
		break;
	  case IValue::Null:
		//		std::cout << *(Null*)evaluated << std::endl;
		std::cout << "Null" << std::endl;
		break;
	}
  }

  return 0;
}
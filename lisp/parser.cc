#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "parser.h"

Number::Number(double number) { this->value_ = number; }
std::pair<Number, string> Number::Parse(string number) {
  auto result = extract_digits(number);
  try {
    return std::make_pair(Number(std::stod(result.first)), result.second);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Malformed number: " << result.first << std::endl;
    assert(false);

  } catch (const std::out_of_range &e) {
    std::cerr << "Number too large" << std::endl;
    assert(false);
  }
}

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

std::pair<Operator, string> Operator::Parse(const string &expr) {

  auto result = extract_operator(expr);

  auto op = result.first;

  if (op == "+")
    return std::make_pair(Operator(Type::Add), result.second);
  else if (op == "-")
    return std::make_pair(Operator(Type::Subtract), result.second);
  else if (op == "*")
    return std::make_pair(Operator(Type::Multiply), result.second);
  else if (op == "/")
    return std::make_pair(Operator(Type::Divide), result.second);

  else {
    std::cerr << "Bad operator: " << op << std::endl;
    assert(false);
  }
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

Expr Expr::Parse(const string &expr) {

  auto str = expr;

  auto num1_parse = Number::Parse(expr);
  str = num1_parse.second;

  str = extract_whitespace(str).second;

  auto op_parse = Operator::Parse(str);
  str = op_parse.second;

  str = extract_whitespace(str).second;

  auto num2_parse = Number::Parse(str);

  auto lhs = num1_parse.first;
  auto op = op_parse.first;
  auto rhs = num2_parse.first;

  return Expr(lhs, rhs, op);
}

Expr::Expr(const Number &lhs, const Number &rhs, const Operator &op)
    : rhs_(rhs), lhs_(lhs), op_(op) {}

std::ostream &operator<<(std::ostream &os, const Expr &e) {
  os << "Expr(" << e.lhs_ << "," << e.rhs_ << "," << e.op_ << ")";
  return os;
}

bool Expr::operator==(const Expr &other) const {
  bool lhs_eq = this->lhs_ == other.lhs_;
  bool rhs_eq = this->rhs_ == other.rhs_;
  bool op_eq = this->op_ == other.op_;
  return lhs_eq && rhs_eq && op_eq;
}

#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include "env.h"
#include "parser.h"

#define log(var) std::cerr << #var << "='" << var << "'" << std::endl;

Number::Number(double number) { this->value_ = number; }
optional<pair<Number, string>> Number::Parse(string number) {
  
  auto result = extract_digits(number);
  if (result.first == "")
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

double Number::get_value() const { return value_; }

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
  auto op = result.value().first;

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

optional<Expr> Expr::Parse(const string &expr) {

  auto str = expr;

  auto num1_parse = Number::Parse(str);
  if (!num1_parse)
    return nullopt;

  str = num1_parse.value().second;

  str = extract_whitespace(str).second;

  auto op_parse = Operator::Parse(str);
  if (!op_parse)
    return nullopt;

  str = op_parse.value().second;

  str = extract_whitespace(str).second;

  auto num2_parse = Number::Parse(str);
  if (!num2_parse)
    return nullopt;

  auto lhs = num1_parse.value().first;
  auto op = op_parse.value().first;
  auto rhs = num2_parse.value().first;

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

Value *Expr::eval() {
  double result;

  switch (op_.type()) {
  case Operator::Add: {
    result = lhs_.get_value() + rhs_.get_value();
    break;
  }
  case Operator::Subtract: {
    result = lhs_.get_value() - rhs_.get_value();
    break;
  }
  case Operator::Multiply: {
    result = lhs_.get_value() * rhs_.get_value();
    break;
  }
  case Operator::Divide: {
    result = lhs_.get_value() / rhs_.get_value();
    break;
  }
  }
  return new Number(result);
}

optional<BindDef> BindDef::Parse(const string &text) {

  // Variiable declaration needs to start with "mat"
  auto tag1 = tag(text, "mat");
  if (!tag1)
    return nullopt;

  auto str = tag1.value().second;

  // Remove following whitespace
  str = extract_whitespace(str).second;

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
  auto expr_parse = Expr::Parse(str);
  if (!expr_parse)
    return nullopt;

  Expr bind_expr = expr_parse.value();

  // Create var
  return optional(BindDef(bind_name, bind_expr));
}

BindDef::BindDef(const std::string &name, const Expr &expr)
    : name_(name), expr_(expr) {}

bool BindDef::operator==(const BindDef &other) const {
  return name_ == other.name_ && expr_ == other.expr_;
}

void BindDef::eval(Env &env) { env.store_binding(name_, this->expr_.eval()); }

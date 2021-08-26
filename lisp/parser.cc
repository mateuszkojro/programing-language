#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "parser.h"

Number::Number(double number) { this->value_ = number; }
Number::Number(string number) {
  try {
    this->value_ = std::stod(number);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Malformed number" << std::endl;
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

Operator::Operator(const string &op) {
  if (op == "+")
    value_ = type::Add;
  else if (op == "-")
    value_ = type::Subtract;
  else if (op == "*")
    value_ = type::Multiply;
  else if (op == "/")
    value_ = type::Divide;
  else {
    std::cerr << "Bad operator: " << op << std::endl;
    assert(false);
  }
}
bool Operator::operator==(const Operator &other) const {
  return this->value_ == other.value_;
}
bool Operator::operator==(const Operator::type &other) const {
  return this->value_ == other;
}

Expr::Parse(const string &expr)
    : lhs_(Number(expr)), rhs_(Number(expr)), op_(Operator(expr)) {}

Expr::Expr(const Number &lhs, const Number &rhs, const Operator &op)
    : rhs_(rhs), lhs_(lhs), op_(op) {}

bool Expr::operator==(const Expr &other) const {
  bool lhs_eq = this->lhs_ == other.lhs_;
  bool rhs_eq = this->rhs_ == other.rhs_;
  bool op_eq = this->op_ == other.op_;
  return lhs_eq && rhs_eq && op_eq;
}

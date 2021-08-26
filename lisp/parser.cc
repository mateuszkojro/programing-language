#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "parser.h"

#define log(var) std::cerr << #var << "='" << var << "'" << std::endl;

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


Operator::Type Operator::type(){
  return this->value_;
}

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

  auto num1_parse = Number::Parse(str);
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

// Value Expr::eval() {
//   double result;

//   switch (op_.type()) {
//     case Operator::Add:{
//       return 
//     }
//     case Operator::Subtract:{
//       return 
//     }
//     case Operator::Multiply:{
//       return 
//     }
//     case Operator::Divide:{
//       return 
//     }
//   }
// }


BindDef BindDef::Parse(const string &text) {

  // Variiable declaration needs to start with "mat"
  auto str = extract(text, "mat").second;

  // Remove following whitespace
  str = extract_whitespace(str).second;

  // Extract the name of the variable
  auto name_parse = extract_identifier(str);
  str = name_parse.second;

  // Save name of the var for later
  auto bind_name = name_parse.first;

  str = extract_whitespace(str).second;

  // Now there needs to be a "="
  str = extract(str, "=").second;

  str = extract_whitespace(str).second;

  // Parse an expresion that should be assigned to var
  auto expr_parse = Expr::Parse(str);

  auto bind_expr = expr_parse;

  // Create var
  return BindDef(bind_name, bind_expr);
}

BindDef::BindDef(const std::string &name, const Expr &expr)
    : name_(name), expr_(expr) {}

bool BindDef::operator==(const BindDef &other) const {
  return name_ == other.name_ && expr_ == other.expr_;
}

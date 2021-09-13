#include "Expr.h"
#include "BindingUsage.h"
#include "Value.h"
#include <utility>

ExprNumber::ExprNumber(const Number &num) : value_(num) {}

bool ExprNumber::operator==(const ExprNumber &other) const {
  return value_ == other.value_;
}

std::ostream &operator<<(std::ostream &os, const ExprNumber &e) {
  os << "Expr(" << e.value_ << ")";
  return os;
}

ExprOperation::ExprOperation(const Number &lhs, const Number &rhs,
                             const Operator &op)
    : lhs_(lhs), rhs_(rhs), op_(op) {}

Value *ExprNumber::eval() { return new Number(value_); }

Value *ExprNumber::eval(Env &env) { return this->eval(); }

bool ExprOperation::operator==(const ExprOperation &other) const {
  bool lhs_eq = this->lhs_ == other.lhs_;
  bool rhs_eq = this->rhs_ == other.rhs_;
  bool op_eq = this->op_ == other.op_;
  return lhs_eq && rhs_eq && op_eq;
}

Value *ExprOperation::eval() {
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

Value *ExprOperation::eval(Env &env) { return this->eval(); }

std::ostream &operator<<(std::ostream &os, const ExprOperation &e) {
  os << "Expr(" << e.lhs_ << "," << e.rhs_ << "," << e.op_ << ")";
  return os;
}

ExprVariable::ExprVariable(BindingUsage *b) : variable_(b) {}

Value *ExprVariable::eval() {
  std::cout << "using var without contex" << std::endl;
  return nullptr;
}

Value *ExprVariable::eval(Env &env) { return variable_->eval(env); }

bool ExprVariable::operator==(const ExprVariable &other) const {
  return *variable_ == *other.variable_;
}

optional<pair<Expr *, string>> Expr::parse(const string &expr) {

  auto str = expr;
  // Value value1;

  // if (auto parsed_number = Number::Parse(str))
  // {
  //   value1 = parsed_number.value().first;
  //   str = parsed_number.value().second;
  // }
  // else if (auto parsed_binding = BindingUsage::parse(str))
  // {
  //   value1 = parsed_binding.value().first;
  //   str = parsed_binding.value().second;
  // }

  if (auto num1_parse = Number::Parse(str)) {

    str = num1_parse.value().second;

    str = extract_whitespace(str).second;

    if (auto op_parse = Operator::Parse(str)) {

      str = op_parse.value().second;

      str = extract_whitespace(str).second;

      auto num2_parse = Number::Parse(str);
      if (!num2_parse)
        return nullopt;

      auto lhs = num1_parse.value().first;
      auto op = op_parse.value().first;
      auto rhs = num2_parse.value().first;

      return make_pair(new ExprOperation(lhs, rhs, op), num2_parse->second);
    } else {
      // Could not parse equation we need to backtrack and parse number
      return make_pair(new ExprNumber(num1_parse->first), num1_parse->second);
    }

  } else if (auto variable = BindingUsage::parse(str)) {
    auto [expr, str] = variable.value();
    return make_pair(new ExprVariable(expr), str);
  }

  return nullopt;
}

ExprBlock::ExprBlock() {}

Value *ExprBlock::eval() {
  assert(false && "This should not be called");
  return nullptr;
}

Value *ExprBlock::ExprBlock::eval(Env &env) {
  assert(false && "Not implemented");
  return nullptr;
}

bool ExprBlock::operator==(const ExprVariable &other) const {
  assert(false && "Not implemented");
  return false;
}

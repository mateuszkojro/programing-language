#include "Expr.h"

#include <utility>

#include "Block.h"
#include "ErrorStatment.h"
#include "Null.h"

ExprNumber::ExprNumber(Number num) : value_(num) {}

bool ExprNumber::operator==(const ExprNumber& other) const {
  return value_ == other.value_;
}

std::ostream& operator<<(std::ostream& os, const ExprNumber& e) {
  os << "IExpr(" << e.value_ << ")";
  return os;
}

ExprOperation::ExprOperation(IStatment* lhs, IStatment* rhs, const Operator& op)
	: lhs_(lhs), rhs_(rhs), op_(op) {}

ExprOperation::ExprOperation(const Number& lhs, const Number& rhs,
							 const Operator& op)
	: lhs_(new Number(lhs)), rhs_(new Number(rhs)), op_(op) {}

IValue* ExprNumber::eval() { return new Number(value_); }

IValue* ExprNumber::eval(Env& env) { return this->eval(); }

bool ExprOperation::operator==(const ExprOperation& other) const {
  bool lhs_eq = this->lhs_ == other.lhs_;
  bool rhs_eq = this->rhs_ == other.rhs_;
  bool op_eq = this->op_ == other.op_;
  return lhs_eq && rhs_eq && op_eq;
}

IValue* ExprOperation::eval() {
  Env env;
  return eval(env);
}

IValue* ExprOperation::eval(Env& env) {
  double result;

  switch (op_.type()) {
	case Operator::Type::Add: {
	  result = lhs_->eval(env)->value() + rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Subtract: {
	  result = lhs_->eval(env)->value() - rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Multiply: {
	  result = lhs_->eval(env)->value() * rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Divide: {
	  result = lhs_->eval(env)->value() / rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Mod: {
	  result =
		  (int64_t)lhs_->eval(env)->value() % (int64_t)rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::IntDivide: {
	  result =
		  (int64_t)lhs_->eval(env)->value() / (int64_t)rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Eq: {
	  result =
		  compare_double(lhs_->eval(env)->value(), rhs_->eval(env)->value());
	  break;
	}
	case Operator::Type::Neq: {
	  result =
		  !compare_double(lhs_->eval(env)->value(), rhs_->eval(env)->value());
	  break;
	}
	case Operator::Type::More: {
	  result = lhs_->eval(env)->value() > rhs_->eval(env)->value();
	  break;
	}
	case Operator::Type::Less: {
	  result = lhs_->eval(env)->value() < rhs_->eval(env)->value();
	  break;
	}
	default: return new ErrorStatment("Operator is not supported");
  }
  return new Number(result);
}

std::ostream& operator<<(std::ostream& os, const ExprOperation& e) {
  os << "IExpr(" << e.lhs_ << "," << e.rhs_ << "," << e.op_ << ")";
  return os;
}

ExprVariable::ExprVariable(BindingUsage* b) : variable_(b) {}

IValue* ExprVariable::eval() {
  FIXME("Using variable without environment");
  return nullptr;
}

IValue* ExprVariable::eval(Env& env) { return variable_->eval(env); }

bool ExprVariable::operator==(const ExprVariable& other) const {
  return *variable_ == *other.variable_;
}

optional<pair<IExpr*, string>> IExpr::parse(const string& expr) {

  auto str = expr;
  // First value is and number
  if (auto parsed_number = Number::parse(str)) {
	Number* value1 = parsed_number->first;
	str = parsed_number->second;
	str = extract_whitespace(str).second;
	// There is operator we continue
	if (auto op = Operator::Parse(str)) {
	  str = op->second;
	  str = extract_whitespace(str).second;
	  // Second element is a number
	  if (auto parsed_number2 = Number::parse(str)) {
		return std::make_pair(
			new ExprOperation(value1, parsed_number2->first, op->first), str);
	  }
	  // Second element is a variable
	  else if (auto parsed_variable2 = BindingUsage::parse(str)) {
		return std::make_pair(
			new ExprOperation(value1, parsed_variable2->first, op->first), str);
	  }
	}
	// There is no operator - it's a simple assigment
	else {
	  return std::make_pair(new ExprNumber(Number(value1->value())), str);
	}
  }
  // First value is a variable
  else if (auto parsed_binding = BindingUsage::parse(str)) {
	BindingUsage* value1 = parsed_binding->first;
	str = parsed_binding->second;
	str = extract_whitespace(str).second;

	// There is operator we continue
	if (auto op = Operator::Parse(str)) {
	  str = op->second;
	  str = extract_whitespace(str).second;
	  // Second element is a number
	  if (auto parsed_number2 = Number::parse(str)) {
		return std::make_pair(
			new ExprOperation(value1, parsed_number2->first, op->first), str);
	  }
	  // Second element is a variable
	  else if (auto parsed_variable2 = BindingUsage::parse(str)) {
		return std::make_pair(
			new ExprOperation(value1, parsed_variable2->first, op->first), str);
	  }

	}
	// There is no operator - it's a simple assigment
	else {
	  return std::make_pair(new ExprVariable(value1), str);
	}
  }
  // Parsing failed
  return std::nullopt;
}

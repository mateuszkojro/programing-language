#ifndef PARSER_H
#define PARSER_H

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

#include "IStatment.h"
#include "IValue.h"
#include "env.h"
#include "utils.h"

using std::optional;
using std::pair;
using std::string;

/**
 * @brief Repersentation of a number in whole language
 */
class Number : public IValue, public IStatment {
 public:
  explicit Number(double number);
  Number(const Number& other)
	  : IValue(IValue::Type::Number), value_(other.value_){};
  /**
   * @deprecated lowerace parse should be used
   */
  static optional<pair<Number, string>> Parse(const string& number);
  static optional<pair<Number*, string>> parse(const string& number);

  bool operator==(const Number& other) const;
  bool operator!=(const Number& other) const;

  /**
   * @brief Returns contained number
   * @return number
   */
  double value() const override;

  /**
   * @deprecated value() should be used
   */
  double get_value() const {
	DEPR("value() should be used instead");
	return value();
  }

  /**
   * @brief Returns itself
   * @param env Scope is ignored
   * @return Itself
   */
  IValue* eval(Env& env) override { return new Number(*this); }

  Number* clone() override;

  ~Number() override = default;

  friend std::ostream& operator<<(std::ostream& os, const Number& n);

 private:
  /**
   * @brief Value represented by the number
   */
  double value_;
};

/**
 * @brief Operators avaliable in the language
 */
class Operator {
 public:
  /**
   * @brief Avaliable operator types
   */
  enum class Type
  {
	Add,
	Subtract,
	Multiply,
	Divide,
	IntDivide,
	Eq,
	Less,
	More,
	Neq,
	Incr,
	Decr,
	Pow,
	Mod,
  };

  static optional<pair<Operator, string>> Parse(const string& op);

  explicit Operator(Type t);
  Operator(const Operator& other) = default;

  /**
   * @brief Getter for the operator type
   * @return Type of the operator
   */
  Type type();

  bool operator==(const Operator& op) const;
  bool operator==(const Operator::Type& op) const;

  ~Operator() = default;

  friend std::ostream& operator<<(std::ostream& os, const Operator& n);

 private:
  /**
   * @brief Type of the operator
   */
  Type value_;
};

/**
 * @brief Class for interpreting strings as a language code
 */
class Interpreter {
 public:
  Interpreter();

  /**
   * @brief Parses given string as a code preserving the enviroment
   * @param code Text to be interpreted as code
   * @return Status code
   */
  int parse(const std::string& code, bool interactive=false);

 private:
  /**
   * @brief Scope that is being preserved between evaluated statments
   */
  Env environment_;
};

#endif// !PARSER_H

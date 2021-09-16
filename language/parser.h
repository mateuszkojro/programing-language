#include "IStatment.h"
#include "IValue.h"
#include "env.h"
#include "utils.h"
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

using std::optional;
using std::pair;
using std::string;

#ifndef PARSER_H
#define PARSER_H

class Number : public IValue, public IStatment {
 public:
  Number(double number);
  static optional<pair<Number, string>> Parse(string number);
  static optional<pair<Number *, string>> parse(string number);

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;

  double value() const;

  double get_value() const { return value(); }

  IValue *eval(Env &env) {
	//	assert(false && "Should not be called temp hack");
	return this;
  }

  ~Number() = default;

  friend std::ostream &operator<<(std::ostream &os, const Number &n);

 private:
  double value_;
};

class Operator {
 public:
  enum Type { Add,
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

  static optional<pair<Operator, string>> Parse(const string &op);
  Operator(Type t);

  Type type();

  bool operator==(const Operator &op) const;
  bool operator==(const Operator::Type &op) const;

  ~Operator() = default;

  friend std::ostream &operator<<(std::ostream &os, const Operator &n);

 private:
  Type value_;
};

class Parser {
 public:
  Parser();
  int parse(const std::string &code);

 private:
  Env environment_;
};

#endif// !PARSER_H

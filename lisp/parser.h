#include "Statment.h"
#include "Value.h"
#include "catch2/catch.hpp"
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

class Number : public Value {
public:
  Number(double number);
  static optional<pair<Number, string>> Parse(string number);

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;

  double get_value() const;

  ~Number() = default;

  friend std::ostream &operator<<(std::ostream &os, const Number &n);

private:
  double value_;
};

class Operator {
public:
  enum Type { Add, Subtract, Multiply, Divide };

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

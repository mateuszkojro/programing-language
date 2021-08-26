#include <cassert>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

using std::string;

struct Extr {
  std::string result;
  std::string rest;

  bool operator==(const Extr& other){
    return result == other.result && rest == other.rest;
  }
};

static Extr extract_digits(const std::string expr) {

  int end = 0;
  for (int i = 0; i < expr.size(); i++) {
    auto znak = expr[i];
    if (std::isdigit(znak))
      end++;
    else
      break;
  }

  Extr extracted;
  extracted.result = expr.substr(0, end);
  extracted.rest = expr.substr(end);
  return extracted;
}

static Extr extract_operator(const std::string expr) {
  char op = expr[0];
  if (op == '+' | op == '-' | op == '*' | op == '/') {
    return {expr.substr(0, 1), expr.substr(1)};
  }
  std::cerr << "Bad operator" << std::endl;
  assert(false);
}

class Number {
public:
  Number(double number);
  Number(string number);

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;

  ~Number() = default;

private:
  double value_;
};

class Operator {
public:
  enum type { Add, Subtract, Multiply, Divide };

  Operator(const string &op);
  bool operator==(const Operator &op) const;
  bool operator==(const Operator::type &op) const;

  ~Operator() = default;

private:
  type value_;
};

class Expr {
public:
  Expr(const string &expr);
  Expr(const Number &lhs, const Number &rhs, const Operator &op);

  bool operator==(const Expr &other) const;

  ~Expr() = default;

private:
  Number lhs_;
  Number rhs_;
  Operator op_;
};
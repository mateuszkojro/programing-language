#ifndef EXPR_H
#define EXPR_H

#include <optional>
#include <string>

#include "parser.h"

using std::optional;
using std::string;

class Expr {
public:
  static optional<Expr> Parse(const string &expr);
  Expr() = default;

  Value *eval() = delete;

  bool operator==(const Expr &other) const = delete;

  ~Expr() = default;
};


class ExprNumber : public Expr {
public:
  ExprNumber(const Number &num);

  Value *eval();

  bool operator==(const ExprNumber &other) const;

  ~ExprNumber() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprNumber &);

private:
  Number value_;
};


class ExprOperation : public Expr {
public:
  ExprOperation(const Number &lhs, const Number &rhs, const Operator &op);

  Value *eval();

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);

private:
  Number lhs_;
  Number rhs_;
  Operator op_;
};

#endif

#ifndef EXPR_H
#define EXPR_H

#include <cassert>
#include <optional>
#include <string>

#include "parser.h"

using std::optional;
using std::string;

class Expr {
public:
  static optional<Expr*> Parse(const string &expr);
  Expr() = default;

  virtual Value *eval() = 0; // { assert(false); };

  // virtual bool operator==(const Expr &other) const { assert(false); };

  ~Expr() = default;
};

class ExprNumber : public Expr {
public:
  ExprNumber(const Number &num);

  virtual Value *eval() override;

  bool operator==(const ExprNumber &other) const;

  ~ExprNumber() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprNumber &);

private:
  Number value_;
};

class ExprOperation : public Expr {
public:
  ExprOperation(const Number &lhs, const Number &rhs, const Operator &op);

  virtual Value *eval() override;

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);

private:
  Number lhs_;
  Number rhs_;
  Operator op_;
};

#endif

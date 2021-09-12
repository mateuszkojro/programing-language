#ifndef EXPR_H
#define EXPR_H

#include <cassert>
#include <memory>
#include <optional>
#include <string>

#include "BindingUsage.h"
#include "Statment.h"
#include "parser.h"

using std::optional;
using std::string;
using std::unique_ptr;

/**
 * @brief Expr Base class for expressions
 *
 */
class Expr : public Statment {
public:
  static optional<pair<Expr *, string>> parse(const string &expr);
  Expr() = default;

  virtual Value *eval() = 0; // { assert(false); };
  virtual Value *eval(Env &env) = 0;
  // virtual bool operator==(const Expr &other) const { assert(false); };

  ~Expr() = default;
};
/**
 * @brief Literal expression for a number ex. &
 *
 */
class ExprNumber : public Expr {
public:
  ExprNumber(const Number &num);

  virtual Value *eval() override;
  virtual Value *eval(Env &env) override;

  bool operator==(const ExprNumber &other) const;

  ~ExprNumber() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprNumber &);

private:
  Number value_;
};

/**
 * @brief Numerical operation ex. 7 + 7
 *
 */
class ExprOperation : public Expr {
public:
  ExprOperation(const Number &lhs, const Number &rhs, const Operator &op);

  virtual Value *eval() override;
  virtual Value *eval(Env &env) override;

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);

private:
  Number lhs_;
  Number rhs_;
  Operator op_;
};

/**
 * @brief usage of arledy existing variable
 *
 */
class ExprVariable : public Expr {
public:
  ExprVariable(BindingUsage *b);
  virtual Value *eval() override;
  virtual Value *eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprVariable() = default;

private:
  unique_ptr<BindingUsage> variable_;
};

class ExprBlock : public Expr {
public:
  ExprBlock();

  virtual Value *eval() override;
  virtual Value *eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprBlock() = default;

private:
};

#endif

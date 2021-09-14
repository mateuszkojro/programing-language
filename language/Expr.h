#ifndef EXPR_H
#define EXPR_H

#include <cassert>
#include <memory>
#include <optional>
#include <string>

#include "BindingUsage.h"
#include "IStatment.h"
#include "parser.h"

using std::optional;
using std::string;
using std::unique_ptr;

/**
 * @brief IExpr Base class for expressions
 *
 */
class IExpr : public IStatment {
 public:
  static optional<pair<IExpr *, string>> parse(const string &expr);
  IExpr() = default;

  //  virtual IValue *eval() = 0;// { assert(false); };
  std::unique_ptr<IValue> eval(Env &env) override = 0;
  // virtual bool operator==(const IExpr &other) const { assert(false); };

  ~IExpr() override = default;
};
/**
 * @brief Literal expression for a number ex. &
 *
 */
class ExprNumber : public IExpr {
 public:
  explicit ExprNumber(const Number &num);

  //  virtual IValue *eval() override;
  std::unique_ptr<IValue> eval(Env &env) override;

  bool operator==(const ExprNumber &other) const;

  ~ExprNumber() override = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprNumber &);

 private:
  Number value_;
};

/**
 * @brief Numerical operation ex. 7 + 7
 *
 */
//class ExprOperationOld : public IExpr {
// public:
//  ExprOperationOld(const Number &lhs, const Number &rhs, const Operator &op);
//
//  virtual IValue *eval() override;
//  virtual IValue *eval(Env &env) override;
//
//  bool operator==(const ExprOperation &other) const;
//
//  ~ExprOperationOld() = default;
//
//  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);
//
// private:
//  Number lhs_;
//  Number rhs_;
//  Operator op_;
//};

class ExprOperation : public IExpr {
 public:
  ExprOperation(IStatment *lhs, IStatment *rhs, const Operator &op);

  //  virtual IValue *eval() override;
  virtual std::unique_ptr<IValue> eval(Env &env) override;

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() override = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);

 private:
  IStatment *lhs_;
  IStatment *rhs_;
  Operator op_;
};

/**
 * @brief usage of arledy existing variable
 *
 */
class ExprVariable : public IExpr {
 public:
  explicit ExprVariable(BindingUsage *b);
  //  virtual IValue *eval() override;
  virtual std::unique_ptr<IValue> eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprVariable() override = default;

 private:
  unique_ptr<BindingUsage> variable_;
};

#endif

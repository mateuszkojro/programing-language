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

  virtual IValue *eval() = 0;// { assert(false); };
  virtual IValue *eval(Env &env) = 0;
  // virtual bool operator==(const IExpr &other) const { assert(false); };

  ~IExpr() = default;
};
/**
 * @brief Literal expression for a number ex. &
 *
 */
class ExprNumber : public IExpr {
 public:
  ExprNumber(const Number &num);

  virtual IValue *eval() override;
  virtual IValue *eval(Env &env) override;

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
class ExprOperation : public IExpr {
 public:
  ExprOperation(IStatment *lhs, IStatment *rhs, const Operator &op);
  ExprOperation(Number lhs, Number rhs, const Operator &op);
  virtual IValue *eval() override;
  virtual IValue *eval(Env &env) override;

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() = default;

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
  ExprVariable(BindingUsage *b);
  virtual IValue *eval() override;
  virtual IValue *eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprVariable() = default;

 private:
  unique_ptr<BindingUsage> variable_;
};

class ExprBlock : public IExpr {
 public:
  ExprBlock();

  virtual IValue *eval() override;
  virtual IValue *eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprBlock() = default;

 private:
};

#endif

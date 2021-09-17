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
 */
class IExpr : public IStatment {
 public:
  static optional<pair<IExpr *, string>> parse(const string &expr);
  IExpr() = default;

  /**
   * @deprecated Should not be used (Mostly there is no sense in evaluating without scope)
   * @brief Evaluate expression
   * @return Value
   */
  virtual IValue *eval() = 0;

  /**
   * @brief Evaluates expression in given scope
   * @param env Current scope
   * @return Evaluated expression
   */
  IValue *eval(Env &env) override = 0;

  ~IExpr() override = default;
};

/**
 * @deprecated Simple Number should be used
 * @brief Literal numeric expression
 */
class ExprNumber : public IExpr {
 public:
  explicit ExprNumber(Number num);

  /**
   * @deprecated Mostly not usefull will be removed
   * @brief Evaluates to a number that is conatined
   * @return Contained Number
   */
  IValue *eval() override;

  /**
   * @brief Evaluates to a number that is conatined
   * @param env Ignored
   * @return Contained Number
   */
  IValue *eval(Env &env) override;

  bool operator==(const ExprNumber &other) const;

  ~ExprNumber() override = default;

  friend std::ostream &operator<<(std::ostream &os, const ExprNumber &);

 private:
  /**
   * @brief Numberic value
   */
  Number value_;
};

/**
 * @brief Mathematical operation (+, -, ==, ...)
 */
class ExprOperation : public IExpr {
 public:
  ExprOperation(IStatment *lhs, IStatment *rhs, const Operator &op);

  /**
   * @deprecated For consistency and extendability sake other constructor should be used
   */
  ExprOperation(const Number &lhs, const Number &rhs, const Operator &op);

  /**
   * @deprecated Mostly not usefull will be removed
   * @brief Evaluates to operation performed on two operands
   * @return Evaluated value
   */
  IValue *eval() override;

  /**
   * @brief Evaluates to operation performed on two operands
   * @param env Scope in wich Statments will be evaluated
   * @return Evaluated value
   */
  IValue *eval(Env &env) override;

  bool operator==(const ExprOperation &other) const;

  ~ExprOperation() override {
	delete lhs_;
	delete rhs_;
  };

  friend std::ostream &operator<<(std::ostream &os, const ExprOperation &);

 private:
  /**
   * @brief Statment on the left hand side of equation
   */
  IStatment *lhs_;

  /**
   * @brief Statment on the right hand side of equation
   */
  IStatment *rhs_;

  /**
   * @brief Operator that will be aplied betwwen evaluated statments
   */
  Operator op_;
};

/**
 * @brief Usage of existing variable
 */
class ExprVariable : public IExpr {
 public:
  explicit ExprVariable(BindingUsage *b);

  /**
   * @deprecated Evaluating variable has no sense without scope
   */
  IValue *eval() override;

  /**
   * @brief Evaluates to value of the variable in scopr
   * @param env Curremt scope
   * @return Value of the variable
   */
  IValue *eval(Env &env) override;
  bool operator==(const ExprVariable &other) const;

  ~ExprVariable() override = default;

 private:
  /**
   * @brief variable
   */
  unique_ptr<BindingUsage> variable_;
};

#endif

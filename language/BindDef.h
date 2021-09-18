#ifndef BIND_DEF_H
#define BIND_DEF_H

#include <optional>
#include <string>
#include <utility>

#include "Expr.h"

using std::optional;
using std::string;

/**
 * @brief Variable binding statment
 * @code
 * mat x = 123
 * @endcode
 */
class BindDef : public IStatment {
 public:
  static optional<pair<BindDef, string>> parse(const string &text);

  BindDef() = delete;
  BindDef(string name, IExpr *expr);
  ~BindDef() override = default; // FIXME We need pass using ptr

  bool operator==(const BindDef &op) const;

  /**
   * @brief Evaluation of Binding stores te value of the binding in current scope and
   * return the evaluated value
   * @param env Current scope
   * @return Evaluated IValue
   */
  IValue *eval(Env &env) override;

 private:
  /***
   * @brief Variable name
   */
  string name_;
  /**
   * @brief Expression that will be evaluated to get variabe value
   */
  IExpr *expr_;
};

#endif

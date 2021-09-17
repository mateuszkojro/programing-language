#ifndef ENV_H
#define ENV_H

#include "IStatment.h"
#include "IValue.h"
#include <optional>
#include <string>
#include <unordered_map>

using std::optional;
using std::string;

class FuncDef;
/**
 * @brief
 */
class Env {
 public:
  /**
   * @brief
   * @param name
   * @param val
   */
  void store_binding(const string &name, IValue *val);

  /**
   * @brief
   * @param name
   * @param val
   */
  void store_function(const string &name, FuncDef *val);

  /**
   * @brief
   * @param name
   * @return
   */
  optional<IValue *> get_binding_value(const string &name);

  /**
   * @brief
   * @param name
   * @return
   */
  optional<FuncDef *> get_function_def(const string &name);

  /**
   * @brief
   * @return
   */
  std::unordered_map<string, IValue *> &get_bindings() { return bindings_; };

 private:

  /**
   * @brief
   */
  std::unordered_map<string, IValue *> bindings_;

  /**
   * @brief
   */
  std::unordered_map<string, FuncDef *> functions_;
};

#endif

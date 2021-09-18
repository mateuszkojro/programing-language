#ifndef ENV_H
#define ENV_H

#include <optional>
#include <string>
#include <unordered_map>

#include "IStatment.h"
#include "IValue.h"

using std::optional;
using std::string;

class FuncDef;
/**
 * @brief Representation of enviroment / scope in the languge
 * (contains maps of function names -> function definitions and variable names
 * -> variable definitions)
 */
class Env {
 public:
  /**
   * @brief Store variable name with coresponding value
   * @param name Name of a variable
   * @param val Value for that variable
   */
  void store_binding(const string& name, IValue* val);

  /**
   * @brief Store function name with coresponding function definition
   * @param name Name for the function
   * @param val Function definition to be assigned
   */
  void store_function(const string& name, FuncDef* val);

  /**
   * @brief Get value coresponding to variable name
   * @param name Name of the variable
   * @return Optional value
   */
  optional<IValue*> get_binding_value(const string& name);

  /**
   * @brief Get Function Definition coresponding to the name
   * @param name Name of the function
   * @return Optional function definition
   */
  optional<FuncDef*> get_function_def(const string& name);

  /**
   * @brief Get a mutable reference to variable bindings
   * @return Reference to variable bindings
   */
  std::unordered_map<string, IValue*>& get_bindings() { return bindings_; };

  ~Env();

 private:
  /**
   * @brief Bindings variable name -> value
   */
  std::unordered_map<string, IValue*> bindings_;

  /**
   * @brief Bindings Function name -> function definitions
   */
  std::unordered_map<string, FuncDef*> functions_;
};

#endif

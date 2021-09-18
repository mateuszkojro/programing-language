#ifndef INTERPRETER_LANGUAGE_FUNCDEF_H_
#define INTERPRETER_LANGUAGE_FUNCDEF_H_

#include <utility>

#include "Block.h"
#include "IStatment.h"

/**
 * @brief Function definitions
 */
class FuncDef : public IStatment {
 public:
  static std::optional<std::pair<FuncDef*, std::string>> parse(
	  const std::string& text);

  FuncDef() = delete;
  FuncDef(std::string func_name, std::vector<std::string> args, Block* body)
	  : name_(std::move(func_name)), body_(body), args_(std::move(args)) {}
  /**
   * @brief Stores function definition in Scope and returns Null
   * @param env Scope in wich function definition should be stored
   * @return Always null
   */
  IValue* eval(Env& env) override;

  /**
   * @brief Getter for names of the arguments used in function body
   * @return Vector of argument names
   */
  const std::vector<std::string>& get_arg_names() { return args_; }

  /**
   * @brief Getter for the function body block
   * @return Pointer to function body block
   */
  Block* get_func_body() { return body_; }
  virtual ~FuncDef();

 private:
  /**
   * @brief Name of the function
   */
  std::string name_;
  /**
   * @brief Names of the arguments
   */
  std::vector<std::string> args_;
  /**
   * @brief Body of the function
   */
  Block* body_;
};

#endif// INTERPRETER_LANGUAGE_FUNCDEF_H_

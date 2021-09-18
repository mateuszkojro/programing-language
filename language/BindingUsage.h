#ifndef BINDING_USAGE_H
#define BINDING_USAGE_H
#include <memory>
#include <string>
#include <utility>

#include "IStatment.h"

using std::pair;
using std::string;

/**
 * @brief Variable binding usage
 * Value can be assigned to variable
 * @code
 * x = 12
 * @endcode
 * or variable can be used in statment
 * @code
 * 12 + x
 * @endcode
 */
class BindingUsage : public IStatment {
 public:
  static optional<pair<BindingUsage*, string>> parse(const string& text);

  explicit BindingUsage(string name);
  BindingUsage(string name, IStatment* new_value);

  ~BindingUsage() override { delete new_value_; };

  bool operator==(const BindingUsage& other) const;

  /**
   * @brief Evaluates variable in scope and returns updated value of the
   * variable
   * @param env Current scope
   * @return Evaluation in current scope
   */
  IValue* eval(Env& env) override;
  BindingUsage* clone() override;

 private:
  /**
   * @brief Variable name
   */
  string name_;
  /**
   * @brief If not null evaluated will be assigned to variable in scope
   */
  IStatment* new_value_ = nullptr;
};

#endif
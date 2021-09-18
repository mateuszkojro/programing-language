#ifndef STATMENT_H
#define STATMENT_H

#include <optional>
#include <string>

#include "IValue.h"

//#include "env.h"

using std::optional;
using std::pair;
using std::string;

class Env;

/**
 * @brief Base class for all possible statments in the language
 */
class IStatment {
 public:
  static optional<pair<IStatment *, string>> parse(const string &str);
  IStatment() = default;

  /**
   * @brief Function uesed to evaluate statment in the scope
   * @param env Scope to evaluate statment in
   * @return Object of the class deriving IValue
   */
  virtual IValue *eval(Env &env) = 0;

  virtual ~IStatment() = default;
};

#endif
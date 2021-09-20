#ifndef NULL_H
#define NULL_H

#include <cmath>

#include "BindDef.h"
#include "IValue.h"

/**
 * @brief Null value
 */
class Null : public IStatment, public IValue {
 public:
  static std::optional<std::pair<Null*, std::string>> parse(
	  const std::string& text);

  Null() : IValue(IValue::Null) {}
  Null(const Null& other) : IValue(Type::Null) {}

  /**
   * @brief Always evaluated to NaN
   * @return NaN
   */
  double value() const override {
	FIXME("Value of Null is implicitly NaN");
	return NAN;
  }

  IValue* eval(Env& env) override { return new Null; }
  Null* clone() override { return new Null(*this); }

  ~Null() override = default;
};

#endif// !NULL_H
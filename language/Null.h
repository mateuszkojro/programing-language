#ifndef NULL_H
#define NULL_H

#include "BindDef.h"
#include "IValue.h"

/**
 * @brief Null value
 */
class Null : public IValue {
 public:
  Null() : IValue(IValue::Null) {}

  /**
   * @brief Always evaluated to NaN
   * @return NaN
   */
  double value() const override {
	FIXME("Value of Null is implicitly NaN");
	return NAN;
  }

  ~Null() override = default;
};

#endif// !NULL_H
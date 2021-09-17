#ifndef NULL_H
#define NULL_H

#include "BindDef.h"
#include "IValue.h"

class Null : public IValue {
 public:
  Null() : IValue(IValue::Null) {}
  double value() const override {
	assert(false && "Tried to get value from null");
	return 0;
  }
  virtual ~Null() = default;
};

#endif// !NULL_H
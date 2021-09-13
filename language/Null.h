#ifndef NULL_H
#define NULL_H

#include "BindDef.h"
#include "IValue.h"

class Null : public IValue {
public:
  Null(): IValue(IValue::Null) {}
  virtual ~Null() = default;
};

#endif // !NULL_H
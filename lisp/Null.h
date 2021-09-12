#ifndef NULL_H
#define NULL_H

#include "BindDef.h"
#include "Value.h"

class Null : public Value {
public:
  Null(): Value(Value::Null) {}
  virtual ~Null() = default;
};

#endif // !NULL_H
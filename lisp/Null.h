#ifndef NULL_H
#define NULL_H

#include "BindDef.h"
#include "Value.h"

class Null : public Value {
public:
  Null() = default;
  virtual ~Null() = default;
};

#endif // !NULL_H
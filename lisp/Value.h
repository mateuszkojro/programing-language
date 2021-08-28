#ifndef VALUE_H
#define VALUE_H

class Value {
public:
  Value() = default;
  virtual ~Value() = default;
  enum Type { Number } type_;
};

#endif

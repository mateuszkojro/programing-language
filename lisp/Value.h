#ifndef VALUE_H
#define VALUE_H

class Value {
public:
  Value() : type_(Value::Number) {}
  virtual ~Value() = default;
  enum Type { Number } type_;
};

#endif

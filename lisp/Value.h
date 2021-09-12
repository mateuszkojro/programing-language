#ifndef VALUE_H
#define VALUE_H

class Value {
public:
  enum Type { Number, Null };

  Value(Type type) : type_(type) {}
  Type get_type() { return type_; }
  virtual ~Value() = default;

private:
  Type type_;
};

#endif

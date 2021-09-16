#ifndef VALUE_H
#define VALUE_H

class IValue {
public:
  enum Type { Number, Null };

  IValue(Type type) : type_(type) {}
  Type get_type() { return type_; }
  virtual double value() const = 0;
  virtual ~IValue() = default;

private:
  Type type_;
};

#endif

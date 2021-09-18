#ifndef VALUE_H
#define VALUE_H

/**
 * @brief Base class for all possible evaluation results
 */
class IValue {
 public:
  /**
   * @brief Type of evaluated value
   */
  enum Type { Number, Null, Error };

  explicit IValue(Type type) : type_(type) {}

  /**
   * @brief Gettet for type of Value
   * @return Type of a value
   */
  Type get_type() { return type_; }

  /**
   * @brief Every value needs to evaluate to double for now later this will be
   * changed to matrix
   * @return Either numeric value or NaN if not correct
   */
  [[nodiscard]] virtual double value() const = 0;

  virtual ~IValue() = default;

 private:
  /**
   * @brief Type of the value
   */
  Type type_;
};

#endif

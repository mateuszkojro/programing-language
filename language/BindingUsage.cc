#include "BindingUsage.h"
#include "Null.h"

#include <string>
#include <utility>

BindingUsage::BindingUsage(const string &name) : name_(name) {}

optional<pair<BindingUsage *, string>> BindingUsage::parse(string text) {
  auto parse_name = extract_identifier(text);
  if (!parse_name)
    return nullopt;

  return std::make_pair(new BindingUsage(parse_name.value().first),
                        parse_name.value().second);
}
bool BindingUsage::operator==(const BindingUsage &other) const {
  return name_ == other.name_;
}
IValue *BindingUsage::eval(Env &env) {
    return env.get_binding_value(name_).value_or(new Null);
}

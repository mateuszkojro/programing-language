#include <cassert>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

using std::nullopt;
using std::optional;
using std::string;
using Str2 = std::pair<string, string>;

#define err(message, value)                                                    \
  do {                                                                         \
    std::cerr << message << value << std::endl;                                \
    std::exit(1);                                                              \
  } while (false)

#define errmsg(message)                                                        \
  do {                                                                         \
    std::cerr << message << std::endl;                                         \
    std::exit(1);                                                              \
  } while (false)

static Str2 take_whle(const string &expr, bool (*func)(char z)) {
  int i = 0;
  while (func(expr[i]))
    i++;
  return Str2(expr.substr(0, i), expr.substr(i));
}

static bool is_digit(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

static bool is_whitespace(char c) {
  return std::isspace(static_cast<unsigned char>(c));
}

static Str2 extract_digits(const std::string expr) {
  return take_whle(expr, is_digit);
}

static Str2 extract_whitespace(const std::string expr) {
  return take_whle(expr, is_whitespace);
}

static optional<Str2> extract_operator(const std::string expr) {
  char op = expr[0];
  if (op == '+' | op == '-' | op == '*' | op == '/') {
    return optional((Str2){expr.substr(0, 1), expr.substr(1)});
  }
  return std::nullopt;
}

static bool is_alphanumeric(char c) { return std::isalpha(c); }

static optional<Str2> tag(const string &text, const string &prefix) {
  if (text.rfind(prefix, 0) == 0) { // pos=0 limits the search to the prefix
    return optional(make_pair(prefix, text.substr(prefix.size())));
  } else {
    return nullopt;
  }
}

static optional<Str2> extract_identifier(const string &text) {
  // FIXME: First character in id can be an number using that we should not
  // allow it
  auto result = take_whle(text, is_alphanumeric);

  if (result.first == "")
    return nullopt;

  return optional(result);
}
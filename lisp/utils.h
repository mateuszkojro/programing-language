#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

using std::string;
using Str2 = std::pair<string, string>;

static void err(string message) {
  std::cerr << message << std::endl;
  std::exit(1);
}

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

static Str2 extract_operator(const std::string expr) {
  char op = expr[0];
  if (op == '+' | op == '-' | op == '*' | op == '/') {
    return {expr.substr(0, 1), expr.substr(1)};
  }
  err("Nad operator");
}

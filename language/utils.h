#include <cassert>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

using std::nullopt;
using std::optional;
using std::string;
using Str2 = std::pair<string, string>;

#ifndef UTILS_H
#define UTILS_H

#define msg(var) std::cerr << #var << "='" << (var) << "'" << std::endl;

#define err(message, value)                                                    \
  do {                                                                         \
	std::cerr << (message) << (value) << std::endl;                            \
	std::exit(1);                                                              \
  } while (false)

#define errmsg(message)                                                        \
  do {                                                                         \
	std::cerr << (message) << std::endl;                                       \
	std::exit(1);                                                              \
  } while (false)

static std::string debug_header(const std::string& title,
								const std::string& file,
								const std::string& function, int line) {
  std::ostringstream ss;
  ss << title << std::endl
	 << "[ " << file << ":" << line << " ] " << function << std::endl;
  return ss.str();
}
static std::string debug_line(const std::string& file,
							  const std::string& function, int line) {
  std::ostringstream ss;
  ss << "[ " << file << ":" << line << " ] " << function << '\t';
  return ss.str();
}
#ifdef NDEBUG

#define FIXME(msg) {};
#define DEPR(msg) {};
#define WARN(msg) {};
#define LOG(msg) {};

#else

#define LOG(msg)                                                               \
  std::cout << debug_line(__FILE__, __FUNCTION__, __LINE__) << msg << std::endl;

#define FIXME(msg)                                                             \
  std::cout << std::endl                                                       \
			<< debug_header("=== FIXME ===", __FILE__, __FUNCTION__, __LINE__) \
			<< (msg) << std::endl                                              \
			<< std::endl

#define DEPR(msg)                                                              \
  std::cout << std::endl                                                       \
			<< debug_header("=== DEPR ===", __FILE__, __FUNCTION__, __LINE__)  \
			<< (msg) << std::endl                                              \
			<< std::endl

#define WARN(msg)                                                              \
  std::cout << std::endl                                                       \
			<< debug_header("=== WARNING ===", __FILE__, __FUNCTION__,         \
							__LINE__)                                          \
			<< (msg) << std::endl                                              \
			<< std::endl
#endif

static std::string ver_string(std::string name, int a, int b, int c) {
  std::ostringstream ss;
  ss << name << " " << a << '.' << b << '.' << c;
  return ss.str();
}
#ifdef _MSC_VER
#define COMPILER ver_string("MSVC", _MSC_VER, 0, 0)
#endif

#ifdef __clang__
#undef COMPILER
#define COMPILER                                                               \
  ver_string("Clang++", __clang_major__, __clang_minor__, __clang_patchlevel__)
#endif

#ifdef __GNUC__
#define COMPILER                                                               \
  ver_string("g++", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#endif

#ifndef COMPILER
#define COMPILER ver_string("Unknown", 0, 0, 0)
#endif

static Str2 take_whle(const string& expr, bool (*func)(char z)) {
  int i = 0;
  while (func(expr[i])) i++;
  return Str2(expr.substr(0, i), expr.substr(i));
}

static bool is_digit(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

static bool is_whitespace(char c) {
  return std::isspace(static_cast<unsigned char>(c)) || c == '\n';
}

static Str2 extract_digits(const std::string& expr) {
  return take_whle(expr, [](char znak) {
	return is_digit(znak) || znak == '.' || znak == '-';
  });
}

static Str2 extract_whitespace(const std::string& expr) {
  return take_whle(expr, is_whitespace);
}

static optional<Str2> extract_operator(const std::string& expr) {
  auto char2 = expr.substr(0, 2);
  if (char2 == "==" || char2 == "!=" || char2 == "//" || char2 == "--"
	  || char2 == "++" || char2 == "**")
	return make_pair(char2, expr.substr(2));
  char op = expr[0];
  if (op == '+' || op == '-' || op == '*' || op == '/' || op == '>' || op == '<'
	  || op == '%')
	return make_pair(expr.substr(0, 1), expr.substr(1));
  return std::nullopt;
}

static bool is_alphanumeric(char c) { return std::isalpha(c); }

static optional<Str2> tag(const string& text, const string& prefix) {
  if (text.rfind(prefix, 0) == 0) {// pos=0 limits the search to the prefix
	return make_pair(prefix, text.substr(prefix.size()));
  } else {
	return nullopt;
  }
}

static bool is_alphanumeric_or_digit(char c) {
  return is_alphanumeric(c) || is_digit(c);
}

static optional<Str2> extract_identifier(const string& text) {
  // FIXME: First character in id can be an number using that we should not
  // allow it
  auto result = take_whle(text, is_alphanumeric_or_digit);

  if (result.first.empty())
	return nullopt;

  if (is_digit(result.first[0]))
	return nullopt;

  return result;
}

static bool compare_double(double a, double b) {
  int N = 10;
  return std::abs(a - b) < std::numeric_limits<double>::epsilon() * N;
};

#endif

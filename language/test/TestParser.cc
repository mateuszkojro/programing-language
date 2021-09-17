#include "../parser.h"
#include <catch2/catch.hpp>
#include <utility>


using std::make_pair;
using std::optional;

TEST_CASE("Parsing numbers is correct", "[Interpreter]") {
  REQUIRE(Number::Parse("123") == optional(make_pair(Number(123), (string) "")));
}

TEST_CASE("Parsing multiply", "[Interpreter]") {
  REQUIRE(Operator::Parse("*") ==
          optional(make_pair(Operator(Operator::Type::Multiply), (string) "")));
}
TEST_CASE("Parsing divide", "[Interpreter]") {
  REQUIRE(Operator::Parse("/") ==
          optional(make_pair(Operator(Operator::Type::Divide), (string) "")));
}
TEST_CASE("Parsing subtract", "[Interpreter]") {
  REQUIRE(Operator::Parse("-") ==
          optional(make_pair(Operator(Operator::Type::Subtract), (string) "")));
}
TEST_CASE("Parsing add", "[Interpreter]") {
  REQUIRE(Operator::Parse("+") ==
          optional(make_pair(Operator(Operator::Type::Add), (string) "")));
}
TEST_CASE("Extracting whitespace", "[Interpreter]") {
  REQUIRE(extract_whitespace(" 1+2") == Str2(" ", "1+2"));
}

TEST_CASE("Extracting whitespace extracts newline", "[Interpreter]") {
  REQUIRE(extract_whitespace("\n1+2") == Str2("\n", "1+2"));
}

TEST_CASE("Extracting whitespace extracts multiple chars", "[Interpreter]") {
  REQUIRE(extract_whitespace("\n 1+2") == Str2("\n ", "1+2"));
}

TEST_CASE("Extracting number", "[Interpreter]") {
  REQUIRE(extract_digits("1+2") == Str2("1", "+2"));
}

TEST_CASE("Extracting operator", "[Interpreter]") {
  REQUIRE(extract_operator("+2") == Str2("+", "2"));
}

TEST_CASE("Extract identifier", "[Interpreter]") {
  REQUIRE(extract_identifier("abc 12") == Str2("abc", " 12"));
}
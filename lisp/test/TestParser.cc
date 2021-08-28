#include "../parser.h"
#include <catch2/catch.hpp>
#include <utility>


using std::make_pair;
using std::optional;

TEST_CASE("Parsing numbers is correct", "[Parser]") {
  REQUIRE(Number::Parse("123") == optional(make_pair(Number(123), (string) "")));
}

TEST_CASE("Parsing multiply", "[Parser]") {
  REQUIRE(Operator::Parse("*") ==
          optional(make_pair(Operator(Operator::Multiply), (string) "")));
}
TEST_CASE("Parsing divide", "[Parser]") {
  REQUIRE(Operator::Parse("/") ==
          optional(make_pair(Operator(Operator::Divide), (string) "")));
}
TEST_CASE("Parsing subtract", "[Parser]") {
  REQUIRE(Operator::Parse("-") ==
          optional(make_pair(Operator(Operator::Subtract), (string) "")));
}
TEST_CASE("Parsing add", "[Parser]") {
  REQUIRE(Operator::Parse("+") ==
          optional(make_pair(Operator(Operator::Add), (string) "")));
}
TEST_CASE("Extracting whitespace", "[Parser]") {
  REQUIRE(extract_whitespace(" 1+2") == Str2(" ", "1+2"));
}

TEST_CASE("Extracting number", "[Parser]") {
  REQUIRE(extract_digits("1+2") == Str2("1", "+2"));
}

TEST_CASE("Extracting operator", "[Parser]") {
  REQUIRE(extract_operator("+2") == Str2("+", "2"));
}

TEST_CASE("Extract identifier", "[Parser]") {
  REQUIRE(extract_identifier("abc 12") == Str2("abc", " 12"));
}
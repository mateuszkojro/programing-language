#include "../parser.h"
#include <catch2/catch.hpp>
#include <utility>

using std::make_pair;

TEST_CASE("Parsing numbers is correct", "[Parser]") {
  REQUIRE(Number::Parse("123") == make_pair(Number(123), (string) ""));
}

TEST_CASE("Parsing multiply", "[Parser]") {
  REQUIRE(Operator::Parse("*") ==
          make_pair(Operator(Operator::Multiply), (string) ""));
}
TEST_CASE("Parsing divide", "[Parser]") {
  REQUIRE(Operator::Parse("/") ==
          make_pair(Operator(Operator::Divide), (string) ""));
}
TEST_CASE("Parsing subtract", "[Parser]") {
  REQUIRE(Operator::Parse("-") ==
          make_pair(Operator(Operator::Subtract), (string) ""));
}
TEST_CASE("Parsing add", "[Parser]") {
  REQUIRE(Operator::Parse("+") ==
          make_pair(Operator(Operator::Add), (string) ""));
}

TEST_CASE("Extracting number", "[Parser]") {
  REQUIRE(extract_digits("1+2") == Str2("1", "+2"));
}

TEST_CASE("Extracting operator", "[Parser]") {
  REQUIRE(extract_operator("+2") == Str2("+", "2"));
}

TEST_CASE("Parsing expression", "[Parser]") {
  REQUIRE(Expr::Parse("1+2") ==
          Expr(Number(1), Number(2), Operator(Operator::Add)));
}
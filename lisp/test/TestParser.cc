#include "../parser.h"
#include <catch2/catch.hpp>

TEST_CASE("Parsing numbers is correct", "[Parser]") {

  Number parsed("123");
  Number raw(123);

  REQUIRE(parsed == raw);
}

TEST_CASE("Parsing multiply", "[Parser]") {
  REQUIRE(Operator("*") == Operator::Multiply);
}
TEST_CASE("Parsing divide", "[Parser]") {
  REQUIRE(Operator("/") == Operator::Divide);
}
TEST_CASE("Parsing subtract", "[Parser]") {
  REQUIRE(Operator("-") == Operator::Subtract);
}
TEST_CASE("Parsing add", "[Parser]") {
  REQUIRE(Operator("+") == Operator::Add);
}

TEST_CASE("Extracting number", "[Parser]") {
  REQUIRE(extract_digits("1+2") == (Extr){"1", "+2"});
}

TEST_CASE("Extracting operator", "[Parser]") {
  REQUIRE(extract_operator("+2") == (Extr){"+", "2"});
}

TEST_CASE("Parsing expression", "[Parser]") {
  REQUIRE(Expr("1+2") == Expr(Number(1),Number(2),Operator("+")));
}
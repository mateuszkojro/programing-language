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

TEST_CASE("Parsing expression", "[Parser]") {
  REQUIRE(Expr::Parse("1+2") ==
          Expr(Number(1), Number(2), Operator(Operator::Add)));
}
TEST_CASE("Parsinng binding", "[Parser]") {
  REQUIRE(BindDef::Parse("mat x = 2 / 4") ==
          BindDef("x", Expr(Number(2), Number(4), Operator(Operator::Divide))));
}
TEST_CASE("Eval divide", "[Parser]") {
  Number *value =
      (Number *)Expr(Number(2), Number(2), Operator(Operator::Divide)).eval();
  REQUIRE(value->get_value() == 1);
}
TEST_CASE("Eval multiply", "[Parser]") {
  Number *value =
      (Number *)Expr(Number(2), Number(3), Operator(Operator::Multiply)).eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Eval subtract", "[Parser]") {
  Number *value =
      (Number *)Expr(Number(2), Number(3), Operator(Operator::Subtract)).eval();
  REQUIRE(value->get_value() == -1);
}
TEST_CASE("Eval add", "[Parser]") {
  Number *value =
      (Number *)Expr(Number(2), Number(3), Operator(Operator::Add)).eval();
  REQUIRE(value->get_value() == 5);
}
TEST_CASE("Parse eval multiply", "[Parser]") {
  Number *value = (Number *)Expr::Parse("2*3").value().eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Parse eval divide", "[Parser]") {
  Number *value = (Number *)Expr::Parse("2/2").value().eval();
  REQUIRE(value->get_value() == 1.0);
}
TEST_CASE("Parse eval subtract", "[Parser]") {
  Number *value = (Number *)Expr::Parse("2-2").value().eval();
  REQUIRE(value->get_value() == 0.0);
}
TEST_CASE("Parse eval add", "[Parser]") {
  Number *value = (Number *)Expr::Parse("2+3").value().eval();
  REQUIRE(value->get_value() == 5.0);
}
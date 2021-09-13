
#include "../Expr.h"
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("Parse eval multiply", "[Parser]") {
  Number *value = (Number *)IExpr::parse("2*3").value().first->eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Parse eval divide", "[Parser]") {
  Number *value = (Number *)IExpr::parse("2/2").value().first->eval();
  REQUIRE(value->get_value() == 1.0);
}
TEST_CASE("Parse eval subtract", "[Parser]") {
  Number *value = (Number *)IExpr::parse("2-2").value().first->eval();
  REQUIRE(value->get_value() == 0.0);
}
TEST_CASE("Parse eval add", "[Parser]") {
  Number *value = (Number *)IExpr::parse("2+3").value().first->eval();
  REQUIRE(value->get_value() == 5.0);
}

TEST_CASE("Eval divide", "[Parser]") {
  Number *value =
      (Number *)ExprOperation(Number(2), Number(2), Operator(Operator::Divide))
          .eval();
  REQUIRE(value->get_value() == 1);
}
TEST_CASE("Eval multiply", "[Parser]") {
  Number *value = (Number *)ExprOperation(Number(2), Number(3),
                                          Operator(Operator::Multiply))
                      .eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Eval subtract", "[Parser]") {
  Number *value = (Number *)ExprOperation(Number(2), Number(3),
                                          Operator(Operator::Subtract))
                      .eval();
  REQUIRE(value->get_value() == -1);
}
TEST_CASE("Eval add", "[Parser]") {
  Number *value =
      (Number *)ExprOperation(Number(2), Number(3), Operator(Operator::Add))
          .eval();
  REQUIRE(value->get_value() == 5);
}

TEST_CASE("Number expr", "[Parser]"){
  Number *value =
      (Number *)ExprNumber(Number(2))
          .eval();
  REQUIRE(value->get_value() == 2);
}

TEST_CASE("Parsing expression", "[Parser]") {
  REQUIRE(*(ExprOperation *)IExpr::parse("1+2").value().first ==
          ExprOperation(Number(1), Number(2), Operator(Operator::Add)));
}


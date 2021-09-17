
#include "../Expr.h"
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("Parse eval multiply", "[Interpreter]") {
  Number *value = (Number *)IExpr::parse("2*3").value().first->eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Parse eval divide", "[Interpreter]") {
  Number *value = (Number *)IExpr::parse("2/2").value().first->eval();
  REQUIRE(value->get_value() == 1.0);
}
TEST_CASE("Parse eval subtract", "[Interpreter]") {
  Number *value = (Number *)IExpr::parse("2-2").value().first->eval();
  REQUIRE(value->get_value() == 0.0);
}
TEST_CASE("Parse eval add", "[Interpreter]") {
  Number *value = (Number *)IExpr::parse("2+3").value().first->eval();
  REQUIRE(value->get_value() == 5.0);
}

TEST_CASE("Eval divide", "[Interpreter]") {
  Number *value =
      (Number *)ExprOperation(Number(2), Number(2), Operator(Operator::Divide))
          .eval();
  REQUIRE(value->get_value() == 1);
}
TEST_CASE("Eval multiply", "[Interpreter]") {
  Number *value = (Number *)ExprOperation(Number(2), Number(3),
                                          Operator(Operator::Multiply))
                      .eval();
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Eval subtract", "[Interpreter]") {
  Number *value = (Number *)ExprOperation(Number(2), Number(3),
                                          Operator(Operator::Subtract))
                      .eval();
  REQUIRE(value->get_value() == -1);
}
TEST_CASE("Eval add", "[Interpreter]") {
  Number *value =
      (Number *)ExprOperation(Number(2), Number(3), Operator(Operator::Add))
          .eval();
  REQUIRE(value->get_value() == 5);
}

TEST_CASE("Number expr", "[Interpreter]"){
  Number *value =
      (Number *)ExprNumber(Number(2))
          .eval();
  REQUIRE(value->get_value() == 2);
}

TEST_CASE("Parsing expression", "[Interpreter]") {
  REQUIRE(*(ExprOperation *)IExpr::parse("1+2").value().first ==
          ExprOperation(Number(1), Number(2), Operator(Operator::Add)));
}


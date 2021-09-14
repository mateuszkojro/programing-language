
#include "../Expr.h"
#include "../Null.h"
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("Parse eval multiply", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2*3").value().first->eval(env);
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Parse eval divide", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2/2").value().first->eval(env);
  REQUIRE(value->get_value() == 1.0);
}
TEST_CASE("Parse eval subtract", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2-2").value().first->eval(env);
  REQUIRE(value->get_value() == 0.0);
}
TEST_CASE("Parse eval add", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2+3").value().first->eval(env);
  REQUIRE(value->get_value() == 5.0);
}

TEST_CASE("Eval divide", "[Parser]") {
  Env env;
  Number n1(2);
  Number n2(2);
  Number *value =
	  (Number *)ExprOperation(&n1, &n2, Operator(Operator::Divide))
		  .eval(env);
  REQUIRE(value->get_value() == 1);
}
TEST_CASE("Eval multiply", "[Parser]") {
  Env env;

  Number n1(2);
  Number n2(3);
  Number *value = (Number *)ExprOperation(&n1, &n2,
										  Operator(Operator::Multiply))
					  .eval(env);
  REQUIRE(value->get_value() == 6);
}
TEST_CASE("Eval subtract", "[Parser]") {
  Env env;

  Number n1(2);
  Number n2(3);
  Number *value = (Number *)ExprOperation(&n1, &n2,
										  Operator(Operator::Subtract))
					  .eval(env);
  REQUIRE(value->get_value() == -1);
}
TEST_CASE("Eval add", "[Parser]") {
  Env env;
  Number n1(2);
  Number n2(3);
  Number *value =
	  (Number *)ExprOperation(&n1, &n2, Operator(Operator::Add))
		  .eval(env);
  REQUIRE(value->get_value() == 5);
}

TEST_CASE("Number expr", "[Parser]") {
  Number *value =
	  (Number *)ExprNumber(Number(2))
		  .eval();
  REQUIRE(value->get_value() == 2);
}

TEST_CASE("Parsing expression", "[Parser]") {
  Number n1(1);
  Number n2(2);

  REQUIRE(*(ExprOperation *)IExpr::parse("1+2")->first == ExprOperation(&n1, &n2, Operator(Operator::Add)));
}
TEST_CASE("Parsing expression with 1 variable", "[Parser]") {
  Number n1(5);
  Number n2(10);

  Env env;
  env.store_binding("a", &n1);

  REQUIRE(*(Number *)IExpr::parse("a+5")->first->eval(env) == n2);

  REQUIRE(*(Number *)IExpr::parse("5+a")->first->eval(env) == n2);
}

TEST_CASE("Parsing expression with 2 variables", "[Parser]") {
  Number n1(5);
  Number n2(10);

  Env env;
  env.store_binding("a", &n1);
  env.store_binding("b", &n1);

  REQUIRE(*(Number *)IExpr::parse("a+b")->first->eval(env) == n2);
}

TEST_CASE("Parsing expression with not defined variable fails", "[Parser]") {
  Env env;
  REQUIRE(IExpr::parse("a+b")->first->eval(env)->get_type() == IValue::Type::Null);
  REQUIRE(IExpr::parse("a+1")->first->eval(env)->get_type() == IValue::Type::Null);
  REQUIRE(IExpr::parse("1+a")->first->eval(env)->get_type() == IValue::Type::Null);
}


#include "../Expr.h"
#include "../Null.h"
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("Parse eval multiply", "[Parser]") {
  Env env;

  Number value = *(Number *)IExpr::parse("2*3").value().first->eval(env).get();
  REQUIRE(value == 6);
}
TEST_CASE("Parse eval divide", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2/2").value().first->eval(env).release();
  REQUIRE(value->get_value() == 1.0);
  delete value;
}
TEST_CASE("Parse eval subtract", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2-2").value().first->eval(env).release();
  REQUIRE(value->get_value() == 0.0);
  delete value;
}
TEST_CASE("Parse eval add", "[Parser]") {
  Env env;

  Number *value = (Number *)IExpr::parse("2+3").value().first->eval(env).release();
  REQUIRE(value->get_value() == 5.0);
  delete value;
}

TEST_CASE("Eval divide", "[Parser]") {
  Env env;
  Number n1(2);
  Number n2(2);
  Number *value =
	  (Number *)ExprOperation(&n1, &n2, Operator(Operator::Divide))
		  .eval(env)
		  .release();
  REQUIRE(value->get_value() == 1);
  delete value;
}
TEST_CASE("Eval multiply", "[Parser]") {
  Env env;

  Number n1(2);
  Number n2(3);
  Number *value = (Number *)ExprOperation(&n1, &n2,
										  Operator(Operator::Multiply))
					  .eval(env)
					  .release();
  REQUIRE(value->get_value() == 6);
  delete value;
}
TEST_CASE("Eval subtract", "[Parser]") {
  Env env;

  Number n1(2);
  Number n2(3);
  Number *value = (Number *)ExprOperation(&n1, &n2,
										  Operator(Operator::Subtract))
					  .eval(env)
					  .release();
  REQUIRE(value->get_value() == -1);
  delete value;
}
TEST_CASE("Eval add", "[Parser]") {
  Env env;
  Number n1(2);
  Number n2(3);
  Number *value =
	  (Number *)ExprOperation(&n1, &n2, Operator(Operator::Add))
		  .eval(env)
		  .release();
  REQUIRE(value->get_value() == 5);
  delete value;
}

TEST_CASE("Eval eq", "[Parser]") {
  Env env;
  Number n1(2);
  Number n2(3);
  Number *value =
	  (Number *)ExprOperation(&n1, &n2, Operator(Operator::Eq))
		  .eval(env)
		  .release();
  REQUIRE(value->get_value() == 0);

  Number *value2 =
	  (Number *)ExprOperation(&n1, &n1, Operator(Operator::Eq)).eval(env).release();

  REQUIRE(value2->get_value() == 1);

  delete value;
  delete value2;
}

TEST_CASE("Parsing eq", "[Parser]") {
  Env env;
  auto [result, str] = IExpr::parse("1==1").value();

  REQUIRE(*(Number *)result->eval(env).get() == Number(1));

  auto [result2, str2] = IExpr::parse("1==2").value();
  REQUIRE(*(Number *)result2->eval(env).get() == Number(0));
}

TEST_CASE("Number expr", "[Parser]") {
  Env env;
  Number *value =
	  (Number *)ExprNumber(Number(2))
		  .eval(env)
		  .release();
  REQUIRE(value->get_value() == 2);
  delete value;
}

TEST_CASE("Parsing expression", "[Parser]") {
  Number n1(1);
  Number n2(2);

  REQUIRE(*(ExprOperation *)IExpr::parse("1+2")->first == ExprOperation(&n1, &n2, Operator(Operator::Add)));
}
TEST_CASE("Parsing expression with 1 variable", "[Parser]") {

  Env env;
  env.store_binding("a", std::make_unique<Number>(5));

  assert(false && "Fixme");
//  REQUIRE(*(Number *)IExpr::parse("a+5")->first->eval(env).get() == n2);
//
//  REQUIRE(*(Number *)IExpr::parse("5+a")->first->eval(env).get() == n2);
}

TEST_CASE("Parsing expression with 2 variables", "[Parser]") {
  Env env;
  env.store_binding("a", std::make_unique<Number>(5));
  env.store_binding("b", std::make_unique<Number>(5));

  REQUIRE(*(Number *)IExpr::parse("a+b")->first->eval(env).get() == std::make_unique<Number>(10)->get_value());
}

TEST_CASE("Parsing expression with not defined variable fails", "[Parser]") {
  Env env;
  REQUIRE(IExpr::parse("a+b")->first->eval(env)->get_type() == IValue::Type::Null);
  REQUIRE(IExpr::parse("a+1")->first->eval(env)->get_type() == IValue::Type::Null);
  REQUIRE(IExpr::parse("1+a")->first->eval(env)->get_type() == IValue::Type::Null);
}

TEST_CASE("Assiging variable to itself", "[Parser]") {
  Env env;
  Number n2(-1);
  env.store_binding("x", std::make_unique<Number>(1));
  auto [value1, str1] = IExpr::parse("x = x").value();
  REQUIRE(*(Number *)value1->eval(env).get() == std::make_unique<Number>(1)->get_value());

  auto [value2, str2] = IExpr::parse("x = x-2").value();
  REQUIRE(*(Number *)value2->eval(env).get() == n2);
}
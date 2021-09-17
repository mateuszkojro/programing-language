#include "../BindDef.h"
#include "../BindingUsage.h"
#include "../Expr.h"
#include "../Null.h"
#include "../env.h"
#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("Parsinng binding operation", "[Interpreter]") {
  auto expr = ExprOperation(Number(2), Number(4), Operator(Operator::Divide));
  REQUIRE(BindDef::parse("mat x = 2 / 4").value().first == BindDef("x", &expr));
}

TEST_CASE("Parsinng binding number", "[Interpreter]") {
  auto expr = ExprNumber(Number(2));
  REQUIRE(BindDef::parse("mat x = 2 ").value().first == BindDef("x", &expr));
}

TEST_CASE("Parse numbers in var name", "[Interpreter]") {
  auto expr = ExprOperation(Number(2), Number(4), Operator(Operator::Divide));
  REQUIRE(BindDef::parse("mat x12 = 2 / 4").value().first ==
          BindDef("x12", &expr));
  REQUIRE(BindDef::parse("mat x12x = 2 / 4").value().first ==
          BindDef("x12x", &expr));
}

TEST_CASE("Dont parse numbers at the start ov var name", "[Interpreter]") {
  REQUIRE(BindDef::parse("mat 12x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::parse("mat 12 = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse vars without name", "[Interpreter]") {
  REQUIRE(BindDef::parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Weird var declaration", "[Interpreter]") {
  REQUIRE(BindDef::parse("xmat x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::parse("mxat x = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without space between let var name", "[Interpreter]") {
  REQUIRE(BindDef::parse("matx = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without var name", "[Interpreter]") {
  REQUIRE(BindDef::parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Bind usgae", "[Interpreter]") {
  auto bu = BindingUsage("x");
  REQUIRE(*BindingUsage::parse("x").value().first == *(&bu));
}

TEST_CASE("Storing binding", "[Interpreter]") {
  Env env;
  Number number(2);
  env.store_binding("x", &number);
  REQUIRE(BindingUsage("x").eval(env)->get_type() == (&number)->get_type());
}

TEST_CASE("Cannot read not existent var", "[Interpreter]") {
  Env env;
  auto n = Null();
  REQUIRE(BindingUsage("x").eval(env)->get_type() == (&n)->get_type());
}
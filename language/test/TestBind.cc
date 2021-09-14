#include "../BindDef.h"
#include "../BindingUsage.h"
#include "../Expr.h"
#include "../Null.h"
#include "../env.h"
#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("Parsinng binding operation", "[Parser]") {
  Number n1(2);
  Number n2(4);

  auto expr = ExprOperation(&n1, &n2, Operator(Operator::Divide));
  REQUIRE(BindDef::parse("mat x = 2 / 4").value().first == BindDef("x", &expr));
}

TEST_CASE("Parsinng binding number", "[Parser]") {
  auto expr = ExprNumber(Number(2));
  REQUIRE(BindDef::parse("mat x = 2 ").value().first == BindDef("x", &expr));
}

TEST_CASE("Parse numbers in var name", "[Parser]") {
  Number n1(2);
  Number n2(4);
  auto expr = ExprOperation(&n1, &n2, Operator(Operator::Divide));
  REQUIRE(BindDef::parse("mat x12 = 2 / 4").value().first == BindDef("x12", &expr));
  REQUIRE(BindDef::parse("mat x12x = 2 / 4").value().first == BindDef("x12x", &expr));
}

TEST_CASE("Dont parse numbers at the start ov var name", "[Parser]") {
  REQUIRE(BindDef::parse("mat 12x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::parse("mat 12 = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse vars without name", "[Parser]") {
  REQUIRE(BindDef::parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Weird var declaration", "[Parser]") {
  REQUIRE(BindDef::parse("xmat x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::parse("mxat x = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without space between let var name", "[Parser]") {
  REQUIRE(BindDef::parse("matx = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without var name", "[Parser]") {
  REQUIRE(BindDef::parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Bind usgae", "[Parser]") {
  auto bu = BindingUsage("x");
  REQUIRE(*BindingUsage::parse("x").value().first == *(&bu));
}

TEST_CASE("Storing binding", "[Parser]") {
  Env env;
  env.store_binding("x", std::make_unique<Number>(2));
  REQUIRE(BindingUsage("x").eval(env)->get_type() == std::make_unique<Number>(2)->get_type());
}

TEST_CASE("Cannot read not existent var", "[Parser]") {
  Env env;
  auto n = Null();
  REQUIRE(BindingUsage("x").eval(env)->get_type() == (&n)->get_type());
}
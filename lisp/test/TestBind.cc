#include "../BindDef.h"
#include "../BindingUsage.h"
#include "../Expr.h"
#include "../env.h"
#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("Parsinng binding operation", "[Parser]") {
  auto expr = ExprOperation(Number(2), Number(4), Operator(Operator::Divide));
  REQUIRE(BindDef::Parse("mat x = 2 / 4").value().first == BindDef("x", &expr));
}

TEST_CASE("Parsinng binding number", "[Parser]") {
  auto expr = ExprNumber(Number(2));
  REQUIRE(BindDef::Parse("mat x = 2 ").value().first == BindDef("x", &expr));
}

TEST_CASE("Parse numbers in var name", "[Parser]") {
  auto expr = ExprOperation(Number(2), Number(4), Operator(Operator::Divide));
  REQUIRE(BindDef::Parse("mat x12 = 2 / 4").value().first ==
          BindDef("x12", &expr));
  REQUIRE(BindDef::Parse("mat x12x = 2 / 4").value().first ==
          BindDef("x12x", &expr));
}

TEST_CASE("Dont parse numbers at the start ov var name", "[Parser]") {
  REQUIRE(BindDef::Parse("mat 12x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::Parse("mat 12 = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse vars without name", "[Parser]") {
  REQUIRE(BindDef::Parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Weird var declaration", "[Parser]") {
  REQUIRE(BindDef::Parse("xmat x = 2 / 4") == std::nullopt);
  REQUIRE(BindDef::Parse("mxat x = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without space between let var name", "[Parser]") {
  REQUIRE(BindDef::Parse("matx = 2 / 4") == std::nullopt);
}

TEST_CASE("Dont parse without var name", "[Parser]") {
  REQUIRE(BindDef::Parse("mat = 2 / 4") == std::nullopt);
}

TEST_CASE("Bind usgae", "[Parser]") {
  REQUIRE(BindingUsage::parse("x").value().first == BindingUsage("x"));
}

TEST_CASE("Storing binding", "[Parser]") {
  Env env;
  Number n(2);
  env.store_binding("x", &n);
  REQUIRE(*(Number *)BindingUsage("x").eval(env).value() == Number(2));
}

TEST_CASE("Cannot read not existent var", "[Parser]") {
  Env env;
  REQUIRE(BindingUsage("x").eval(env) == std::nullopt);
}
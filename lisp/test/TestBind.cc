#include "../BindDef.h"
#include "../Expr.h"
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("Parsinng binding operation", "[Parser]") {
  auto expr = ExprOperation(Number(2), Number(4), Operator(Operator::Divide));
  REQUIRE(BindDef::Parse("mat x = 2 / 4") == optional(BindDef("x", &expr)));
}

TEST_CASE("Parsinng binding number", "[Parser]") {
  auto expr = ExprNumber(Number(2));
  REQUIRE(BindDef::Parse("mat x = 2 ") == optional(BindDef("x", &expr)));
}

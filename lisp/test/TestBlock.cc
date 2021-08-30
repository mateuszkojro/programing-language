#include "../Block.h"
#include "../Expr.h"
#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("Parsing empyt block", "[Block]") {
  REQUIRE(Block::parse("{}").value().first == Block({}));
}
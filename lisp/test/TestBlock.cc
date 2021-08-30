#include "../Block.h"
#include "../Expr.h"
#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("Parsing empty block", "[Block]") {
  REQUIRE(Block::parse("{}").value().first == Block({}));
}

TEST_CASE("Parsing empty block with whitespace", "[Block]") {
  REQUIRE(Block::parse("{  }").value().first == Block({}));
}

TEST_CASE("Parsing block with one statment", "[Block]") {
  ExprNumber n(5);
  vector<Statment *> block = {&n};
  REQUIRE(Block::parse("{ 5 }").value().first == Block(block));
}

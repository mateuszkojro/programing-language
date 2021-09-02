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

// TODO: For now assigment operations evaluate to the value that is being
// assigned
TEST_CASE("Parsing block with multiple statments", "[Block]") {
  ExprOperation o(Number(5), Number(5), Operator(Operator::Add));
  ExprNumber n(5);
  vector<Statment *> block = {&n, &o, &n};
  REQUIRE(Block::parse("{ mat x = 5  5 + 5  5 }").value().first ==
          Block(block));
}

TEST_CASE("Parsing block with assigning variable to variable", "[Fail]") {
  ExprNumber a(5);
  ExprNumber b(5);
  vector<Statment *> block = {&a, &b, &b};
  REQUIRE(Block::parse("{ mat a = 5  mat b = a  b}").value().first ==
          Block(block));
}

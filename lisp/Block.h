#include <utility>
#ifndef BLOCK_H
#define BLOCK_H value

#include "Expr.h"
#include <optional>
#include <vector>

using std::optional;
using std::pair;
using std::string;
using std::vector;

class Block {
public:
  static optional<pair<Block, string>> parse(const string &text);
  Block(const vector<Expr*> &exprs);
  ~Block() = default;

  bool operator==(const Block &other) const;

private:
  vector<Expr*> exprs_;
};

#endif
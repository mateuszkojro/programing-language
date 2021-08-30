#include "Block.h"

optional<pair<Block, string>> Block::parse(const string &text) {

    

}

Block::Block(const vector<Expr *> &exprs): exprs_(exprs) {}

bool Block::operator==(const Block &other) const {

  if (exprs_.size() != other.exprs_.size())
    return false;

  for (int i = 0; i < exprs_.size(); i++) {
    if (exprs_[i]->eval() != other.exprs_[i]->eval())
      return false;
  }

  return true;
}

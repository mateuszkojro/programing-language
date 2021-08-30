#include "Block.h"

optional<pair<Block, string>> Block::parse(const string &text) {



    
}

Block::Block(const vector<Statment *> &statments) : statments_(statments) {}


// FIXME: what to do with those envs
bool Block::operator==(const Block &other) const {

  Env env;

  if (statments_.size() != other.statments_.size())
    return false;

  for (int i = 0; i < statments_.size(); i++) {
    if (statments_[i]->eval(env) != other.statments_[i]->eval(env))
      return false;
  }

  return true;
}

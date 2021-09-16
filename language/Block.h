#ifndef BLOCK_H
#define BLOCK_H value

#include "IStatment.h"
#include <optional>
#include <string>
#include <vector>

using std::optional;
using std::pair;
using std::string;
using std::vector;

class Block {
public:
  static optional<pair<Block, string>> parse(const string &text);
  Block(const vector<IStatment *> &exprs);
  ~Block() = default;

  bool operator==(const Block &other) const;
  IValue * eval(Env& env);

private:
  vector<IStatment *> statments_;
};

#endif
#ifndef BLOCK_H
#define BLOCK_H value

#include "Statment.h"
#include <optional>
#include <vector>
#include <string>

using std::optional;
using std::pair;
using std::string;
using std::vector;

class Block {
public:
  static optional<pair<Block, string>> parse(const string &text);
  Block(const vector<Statment*> &exprs);
  ~Block() = default;

  bool operator==(const Block &other) const;

private:
  vector<Statment*> statments_;
};

#endif
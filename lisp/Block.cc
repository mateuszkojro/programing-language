#include "Block.h"
#include "utils.h"
#include <cmath>

#include "parser.h"

optional<pair<Block, string>> Block::parse(const string &text) {
  auto open_block = tag(text, "{");
  if (!open_block)
    return nullopt;

  string str = open_block.value().second;

  str = extract_whitespace(str).second;

  vector<Statment *> statments;

  auto parse_statment = Statment::parse(str);
  while (parse_statment) {

    // msg(str);

    str = parse_statment.value().second;

    statments.push_back(parse_statment.value().first);

    str = extract_whitespace(str).second;

    parse_statment = Statment::parse(str);
  }

  auto close_block = tag(str, "}");
  if (!close_block)
    return nullopt;

  return pair(Block(statments), str);
}

Block::Block(const vector<Statment *> &statments) : statments_(statments) {}

// FIXME: what to do with those envs
bool Block::operator==(const Block &other) const {

  Env env;

  if (statments_.size() != other.statments_.size())
    return false;

  for (int i = 0; i < statments_.size(); i++) {
    Number *n1 = (Number *)statments_[i]->eval(env);
    Number *n2 = (Number *)other.statments_[i]->eval(env);

    if (n1->get_value() != n2->get_value())
      return false;
  }

  return true;
}

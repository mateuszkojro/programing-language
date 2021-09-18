#ifndef BLOCK_H
#define BLOCK_H value

#include <optional>
#include <string>
#include <vector>

#include "IStatment.h"

using std::optional;
using std::pair;
using std::string;
using std::vector;

/**
 * @brief Code blocks - scopes
 * Always evaluate to the last statment in them
 * for example:
 * @code
 * {1 2 4}
 * @endcode
 * evaluates to 4
 *
 * Blocs can be ussd both as a separate construct:
 * @code
 * x = { mat x = 0 x }
 * @endcode
 * and part of other language constructs (if statments, while loops, function
 * definitions)
 * @code
 * if (1) {10}
 * @endcode
 */
class Block : public IStatment {
 public:
  static optional<pair<Block*, string>> parse(const string& text);

  /**
   * @deprecated For consistency parse should be used instead
   */
  static optional<pair<Block, string>> Parse(const string& text);

  explicit Block(const vector<IStatment*>& exprs);
  ~Block() override {
	for (auto statment : statments_) { delete statment; }
  };
  bool operator==(const Block& other) const;

  /**
   * @brief Evaluates all statment in block in current scope
   * @param env Scope to evaluate block in
   * @return Evaluation of the last statment in the block
   */
  IValue* eval(Env& env) override;
  Block* clone() override;

 private:
  /**
   * @brief List of statments in the block
   */
  vector<IStatment*> statments_;
};

#endif
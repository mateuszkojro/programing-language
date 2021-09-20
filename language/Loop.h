#ifndef INTERPRETER_LANGUAGE_LOOP_H_
#define INTERPRETER_LANGUAGE_LOOP_H_

#include "Block.h"
#include "IStatment.h"

/**
 * @brief While loop statments
 */
class Loop : public IStatment {
 public:
  static std::optional<std::pair<IStatment*, std::string>> parse(
	  const std::string& text);

  Loop(IStatment* condition, Block* bloc);
  Loop(const Loop& other)
	  : block_(other.block_->clone()), condition_(other.condition_->clone()) {}
  ~Loop() override;
  /**
   * @brief Evaluates all statments in block as long as condition is true
   * @param env Scope in wich the loop should be evaluated
   * @return Last value in the block during the last evaluation of the loop
   * block
   */
  IValue* eval(Env& env) override;
  Loop* clone() override;

 private:
  /**
   * @brief Condition that determines if loop should continue
   */
  IStatment* condition_;

  /**
   * @brief Block of statments that will be executed while Condition is true
   */
  Block* block_;
};

#endif// INTERPRETER_LANGUAGE_LOOP_H_

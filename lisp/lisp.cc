#include <iostream>

#include "lisp.h"
#include "tokens/Main.h"

namespace ls {

Interpreter::Interpreter() { parsing_token_ = new Main(); }

int Interpreter::interpret(const std::string &text) {
  for (char znak : text) {
    auto next_token = parsing_token_->parse(znak, stack_);

    if (next_token != parsing_token_) {
      // TODO: I dont know if i should delete that
      // delete parsing_token_; // do i tho? if it is also pushed to the stack
      parsing_token_ = next_token;
    }
  }
}
} // namespace ls
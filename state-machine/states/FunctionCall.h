//
// Created by mateu on 6/4/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H

#include <utility>
#include <Function.h>

#include "Token.h"
#include "State.h"
#include "Scope.h"
#include "../Utility.h"

/// \brief State used for FUNCTION calls
class FunctionCall : public State {
  /// \brief return value from called FUNCTION if FUNCTION returns nullptr else
  Variable *target_token_;
  /// \brief Name of the FUNCTION to be called
  std::string function_name_;

  /// \brief used for building up variables to be passed to a FUNCTION
  std::string buffer_;

  /// \brief Cleans up the stack after exiting functions SCOPE
  void clean() {
	Token *token = stack_.Back();
	while (token->GetName() != function_name_ + "Call") {
	  stack_.PopBack();
	  token = stack_.Back();
	}
	stack_.PopBack();
  }

 public:
  FunctionCall(Stack &stack, std::string buffer, Token *token);

  State *Parse(const std::string &text, int position) override;

  ~FunctionCall();
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H

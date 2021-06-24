//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

#include "Variable.h"
#include "Matrix.h"
#include "Stack.h"

class Utility {
 public:
  static Token *FindToken(const Stack &stack, const std::string &token_name) {
	for (Token *token: stack.GetData()) {
	  if (token->GetName() == token_name)
		return token;
	}
	return nullptr;
  }

  static bool whitespace(char letter) {
	switch (letter) {
	  case '\n':
	  case '\t':
	  case '\r':
	  case ' ':return true;
	  default:return false;
	}
  }
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

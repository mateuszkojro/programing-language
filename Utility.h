//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

#include "Variable.h"
#include "Matrix.h"

class Utility {
public:
    static Token *find_token(const Stack &stack, const std::string &token_name) {
        for (Token *token: stack) {
            if (token->get_name() == token_name)
                return token;
        }
        return nullptr;
    }

    static bool whitespace(char letter) {
        switch (letter) {
            case '\n':
            case '\t':
            case '\r':
            case ' ':
                return true;
            default:
                return false;
        }
    }

  static Matrix &get_from_stack(Stack &stack) {
	Variable *var = (Variable *) stack.back();
	stack.pop_back();
	return variable->get_value();
  }
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

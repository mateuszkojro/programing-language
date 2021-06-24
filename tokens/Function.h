//
// Created by mateu on 6/4/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H

#include <string>
#include <functional>
#include <utility>
#include "Token.h"
#include "../Stack.h"

#define FUNCTION_TYPE std::function<int(Stack&)>

class Function : public Token {
  std::string name_;

  FUNCTION_TYPE function_;

 public:
  Function(std::string name, FUNCTION_TYPE function)
	  : name_(std::move(name)), function_(std::move(function)) {};

  const std::string &GetName() override;

  TokenType GetType() override;

  FUNCTION_TYPE GetValue();

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H

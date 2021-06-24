//
// Created by mateu on 6/24/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE__STACK_H_
#define UI4_PROGRAMOWANIE_OBIEKTOWE__STACK_H_

#include <vector>
#include "Token.h"

class Stack {
public:

  void PushBack(Token* token);
  void PopBack();

  std::vector<Token*>& GetData();

  [[nodiscard]]
  const std::vector<Token*>& GetData() const;

  std::vector<Token*> data_;
  Token *Back();
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE__STACK_H_

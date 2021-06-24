//
// Created by mateu on 6/24/2021.
//

#include "Stack.h"
void Stack::PushBack(Token *token) {
  data_.push_back(token);
}
void Stack::PopBack() {
  data_.pop_back();
}
Token *Stack::Back() {
  return data_.back();
}
std::vector<Token *> &Stack::GetData() {
  return data_;
}
const std::vector<Token *> &Stack::GetData() const {
  return data_;
}

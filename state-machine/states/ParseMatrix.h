//
// Created by mateu on 6/24/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_MACHINE_STATES_PARSEMATRIX_H_
#define UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_MACHINE_STATES_PARSEMATRIX_H_

#include "State.h"
#include "../../Matrix.h"
#include "../../Stack.h"

/// \brief State used for creating rows_ in matrix_
class RowState : public State {

 public:
  RowState(Stack &stack, Matrix &matrix);
  State *Parse(const std::string &text, int position) override;

 private:
  /// \brief Matrix val that is being build
  Matrix &matrix_;
  /// \brief Temporary buffer_
  std::string buffer_;

};

/// \brief State used for creating first row in Matrix
class FirstRowState : public State {

 public:
  FirstRowState(Stack &stack, Matrix &matrix);
  State *Parse(const std::string &text, int position) override;

 private:
  /// \brief Matrix val that is being build
  Matrix &matrix_;
  /// \brief if the matrix_ being parsed is a string literal we need to act differently
  bool is_string_;
  /// \brief Temporary buffer_
  std::string buffer_;

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_MACHINE_STATES_PARSEMATRIX_H_

//
// Created by mateu on 6/3/2021.
//

#include <State.h>
#include <cassert>
#include <states/ParseMatrix.h>
#include "Matrix.h"
#include "Stack.h"

/// Function that parses a matrix_ and assigns it into @matrix
/// \param code code to be parsed
/// \param matrix matrix_ to bullied up
/// \return true if parsing completed successfully and false if it failed
bool Matrix::ParseMatrix(const std::string &code, Matrix &matrix) {
  Stack stack;
  if (code == "null") {
	return true;
  }
  State *current_state = new FirstRowState(stack, matrix);
  for (int i = 1; i < code.size(); i++) {
	State *next_state = current_state->Parse(code, i);
	if (next_state == nullptr)
	  return true;
	if (current_state != next_state) {
	  delete current_state;
	  current_state = next_state;
	}
  }
  return false;
}

// Thanks to https://github.com/piotr233 for impl
/// Create string representing the matrix_
/// \return string representation of the matrix_
std::string Matrix::Repr() {

  std::string out;
  out += "[";
  for (unsigned i = 0; i < rows_; i++) {
	out += "[";
	for (unsigned j = 0; j < cols_; j++) {
	  out += std::to_string(data_[i * cols_ + j]);
	  if (j != cols_ - 1)
		out += ", ";
	}
	out += "]";
	if (i != rows_ - 1) out += "\n";
  }
  out += "]\n";
  return out;
}
bool Matrix::IsMatrix(const std::string &buffer) {

  return (buffer[0] == '[' && buffer[1] == '[') || buffer == "null" || buffer[0] == '"';
}
void Matrix::AddColumn() {
  assert(rows_ == 1);
  cols_ += 1;
}
void Matrix::AddRow() {
  rows_ += 1;
  assert(cols_ == streak_);
  streak_ = 0;
}

bool Matrix::AddValue(double value) {
  streak_ += 1;
  if (streak_ > cols_)
	return false;
  data_.push_back(value);
  return true;
}

bool Matrix::operator==(const Matrix &other) const {
  if (cols_ != other.cols_)
	return false;
  if (rows_ != other.rows_)
	return false;
  for (int i = 0; i < data_.size(); i++) {
	if (data_[i] != other.data_[i]) {
	  return false;
	}
  }
  return true;
}

Matrix::Matrix(bool val) : cols_(1), rows_(1), streak_(1) {
  if (val)
	data_.push_back(1);
  else
	data_.push_back(0);
}

int Matrix::Translate(int row, int col) const {
  return row * rows_ + col;
}

double &Matrix::operator()(int idx) {
  return data_.at(idx);
}

double &Matrix::operator()(int row, int col) {
  return data_.at(Translate(row, col));
}

double Matrix::Get(int position) {
  return data_.at(position);
}

unsigned long long int Matrix::Size() {
  return data_.size();
}

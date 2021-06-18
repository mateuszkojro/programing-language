//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H

#include <cassert>
#include <string>
#include <vector>
#include <deque>

#include "Token.h"
#include "State.h"
#include "Utility.h"

class Matrix {
 public:

  static bool ParseMatrix(const std::string &code, Matrix &matrix);

  static bool IsMatrix(const std::string &buffer) {

	return (buffer[0] == '[' && buffer[1] == '[') || buffer == "null" || buffer[0] == '"';
  }

  void AddColumn() {
	assert(rows_ == 1);
	cols_ += 1;
  }

  void AddRow() {
	rows_ += 1;
	assert(cols_ == streak_);
	streak_ = 0;
  }

  bool AddValue(double value) {
	streak_ += 1;
	if (streak_ > cols_)
	  return false;
	data_.push_back(value);
	return true;
  }

  bool operator==(const Matrix &other) const {
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

  Matrix() : cols_(0), rows_(0), streak_(0) {}

  explicit Matrix(bool val) : cols_(1), rows_(1), streak_(1) {
	if (val)
	  data_.push_back(1);
	else
	  data_.push_back(0);
  }

  double Get(int position) {
	return data_.at(position);
  }

  double Size() {
	return data_.size();
  }

  std::string Repr();


 private:
  int streak_;
  int cols_;
  int rows_;
  std::vector<double> data_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H

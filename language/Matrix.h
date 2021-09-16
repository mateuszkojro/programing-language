//
// Created by mateu on 9/16/2021.
//

#ifndef INTERPRETER_LANGUAGE_MATRIX_H_
#define INTERPRETER_LANGUAGE_MATRIX_H_

#include "IStatment.h"

class Matrix : public IValue, public IStatment {
 public:
  Matrix(int rows, int cols, const std::vector<double> &data);
  //  static optional<pair<Matrix, string>> Parse(string value);
  static optional<pair<Matrix *, string>> parse(string value);

  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;
  bool operator*(const Matrix &other) const;
  bool operator%(const Matrix &other) const;
  bool operator>(const Matrix &other) const;
  bool operator<(const Matrix &other) const;
  bool operator+(const Matrix &other) const;
  bool operator-(const Matrix &other) const;

  double value() const;

  double get_value() const { return value(); }

  IValue *eval(Env &env) {
	//	assert(false && "Should not be called temp hack");
	return this;
  }

  ~Matrix() = default;

  friend std::ostream &operator<<(std::ostream &os, const Matrix &n);

 private:
  int rows_;
  int cols_;
  std::vector<double> value_;
};

#endif//INTERPRETER_LANGUAGE_MATRIX_H_

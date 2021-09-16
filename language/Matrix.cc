//
// Created by mateu on 9/16/2021.
//

#include "Matrix.h"
optional<pair<Matrix *, string>> Matrix::parse(string value) {
  return optional<pair<Matrix *, string>>();
}
Matrix::Matrix(int rows, int cols, const std::vector<double> &data) : IValue(Type::Number) {
}
bool Matrix::operator==(const Matrix &other) const {
  return false;
}
bool Matrix::operator!=(const Matrix &other) const {
  return false;
}
bool Matrix::operator*(const Matrix &other) const {
  return false;
}
bool Matrix::operator%(const Matrix &other) const {
  return false;
}
bool Matrix::operator>(const Matrix &other) const {
  return false;
}
bool Matrix::operator<(const Matrix &other) const {
  return false;
}
bool Matrix::operator+(const Matrix &other) const {
  return false;
}
bool Matrix::operator-(const Matrix &other) const {
  return false;
}
double Matrix::value() const {
  return 0;
}

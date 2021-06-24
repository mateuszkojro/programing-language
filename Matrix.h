//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H

#include <string>
#include <vector>

class Matrix {
 public:

  static bool ParseMatrix(const std::string &code, Matrix &matrix);

  static bool IsMatrix(const std::string &buffer);

  void AddColumn();

  void AddRow();

  bool AddValue(double value);

  bool operator==(const Matrix &other) const;

  Matrix() : cols_(0), rows_(0), streak_(0) {}

  explicit Matrix(bool val);

  [[nodiscard]]
  int Translate(int row, int col) const;

  double &operator()(int idx);

  double &operator()(int row, int col);

  double Get(int position);

  unsigned long long int Size();

  std::string Repr();

 private:
  int streak_;
  int cols_;
  int rows_;
  std::vector<double> data_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H

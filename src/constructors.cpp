#include "s21_matrix_oop.h"

double** alloc_memory(int rows, int columns) {
  double** res = new double*[rows];
  for (int i = 0; i < rows && res; i++) {
    res[i] = new double[columns]();
    if (!res[i]) {
      for (int j = 0; j < i; j++) {
        delete[] res[j];
        res[j] = nullptr;
      }
      delete[] res;
      res = nullptr;
    }
  }
  return res;
}

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = alloc_memory(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 and cols > 0) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = alloc_memory(rows_, cols_);
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = alloc_memory(rows_, cols_);
  if (matrix_)
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

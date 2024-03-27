#include <stdexcept>

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(S21Matrix& mat_1) {
  S21Matrix res_mat(*this);
  res_mat.SumMatrix(mat_1);
  return res_mat;
}

S21Matrix S21Matrix::operator-(S21Matrix& mat_1) {
  S21Matrix res_mat(*this);
  res_mat.SubMatrix(mat_1);
  return res_mat;
}

S21Matrix S21Matrix::operator*(S21Matrix& mat) {
  S21Matrix res_mat(*this);
  res_mat.MulMatrix(mat);
  return res_mat;
}

S21Matrix operator*(double x, S21Matrix& mat) {
  S21Matrix res_mat(mat);
  res_mat.MulNumber(x);
  return res_mat;
}

S21Matrix operator*(S21Matrix& mat, double x) {
  S21Matrix res_mat(mat);
  res_mat.MulNumber(x);
  return res_mat;
}

bool S21Matrix::operator==(S21Matrix& mat) { return this->EqMatrix(mat); }

void S21Matrix::operator=(S21Matrix& mat) {
  this->~S21Matrix();
  S21Matrix tmp_mat(mat);
}

void S21Matrix::operator+=(S21Matrix& mat) { this->SumMatrix(mat); }

void S21Matrix::operator-=(S21Matrix& mat) { this->SubMatrix(mat); }

void S21Matrix::operator*=(S21Matrix& mat) { this->MulMatrix(mat); }

void S21Matrix::operator*=(double x) { this->MulNumber(x); }

double S21Matrix::operator()(int i, int j) {
  if (i >= 0 and i <= rows_ and j >= 0 and j <= cols_)
    return matrix_[i][j];
  else
    throw std::out_of_range("Index is outside the matrix.");
}

double* S21Matrix::operator[](int i) {
  if (i >= 0 and i < rows_)
    return matrix_[i];
  else
    throw std::out_of_range("Index is outside the matrix.");
}

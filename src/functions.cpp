#include <cmath>
#include <stdexcept>

#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (rows_ == other.rows_ and cols_ == other.cols_) {
    for (int i = 0; i < rows_ and res; i++)
      for (int j = 0; j < cols_ and res; j++)
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) res = false;
  } else
    res = false;
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ and cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  } else
    throw std::domain_error("Different matrix dimensions");
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ and cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  } else
    throw std::domain_error("Different matrix dimensions");
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ == other.rows_) {
    // Creating new matrix
    double** tmp_mat = new double*[rows_];
    for (int i = 0; i < rows_ and tmp_mat; i++) {
      tmp_mat[i] = new double[other.cols_]();
      if (!tmp_mat[i]) {
        for (int j = 0; j < i; j++) {
          delete[] tmp_mat[j];
          tmp_mat[j] = nullptr;
        }
        delete[] tmp_mat;
        tmp_mat = nullptr;
      }
    }
    // Filling the matrix
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < other.cols_; j++)
        for (int k = 0; k < cols_; k++)
          tmp_mat[i][j] += matrix_[i][k] * other.matrix_[k][j];
    // Deleting previous matrix
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
    // Assigning new matrix to the previous one
    matrix_ = tmp_mat;
    cols_ = other.cols_;
  } else
    throw std::domain_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res_mat(cols_, rows_);
  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < rows_; j++) res_mat.matrix_[i][j] = matrix_[j][i];
  return res_mat;
}

S21Matrix S21Matrix::get_supporting_mat(int row, int column) {
  S21Matrix res_mat(rows_ - 1, cols_ - 1);
  int row_index = 0;
  int col_index = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      for (int j = 0; j < cols_; j++) {
        if (j != column) {
          res_mat.matrix_[row_index][col_index] = matrix_[i][j];
          col_index++;
        }
      }
      col_index = 0;
      row_index++;
    }
  }
  return res_mat;
}

double S21Matrix::Determinant() {
  if (rows_ == cols_) {
    double res = 0;
    if (rows_ == 1)
      res = matrix_[0][0];
    else {
      for (int i = 0; i < cols_; i++) {
        S21Matrix supporting_mat = get_supporting_mat(0, i);
        res += matrix_[0][i] * pow(-1, i) * supporting_mat.Determinant();
      }
    }
    return res;
  } else
    throw std::domain_error("The matrix is not square.");
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ == cols_) {
    S21Matrix res_mat(rows_, cols_);
    if (rows_ == 1)
      res_mat[0][0] = 1;
    else
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
          res_mat.matrix_[i][j] =
              pow(-1, i + j) * get_supporting_mat(i, j).Determinant();
    return res_mat;
  } else
    throw std::domain_error("The matrix is not square.");
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ == cols_) {
    double det = Determinant();
    if (fabs(det) > 1e-6) {
      S21Matrix res_mat = CalcComplements().Transpose();
      res_mat.MulNumber(1 / det);
      return res_mat;
    } else
      throw std::out_of_range("Matrix determinant is zero");
  } else
    throw std::domain_error("The matrix is not square.");
}
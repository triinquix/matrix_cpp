#include "s21_matrix_oop.h"

int S21Matrix::get_num_of_columns() { return cols_; }
int S21Matrix::get_num_of_rows() { return rows_; }

void S21Matrix::set_num_of_rows(int num_of_rows) {
  if (num_of_rows) {
    // Creating a matrix copy
    double** tmp_mat = new double*[num_of_rows];
    for (int i = 0; i < num_of_rows; i++) tmp_mat[i] = new double[cols_]();
    int iterator = rows_;
    if (num_of_rows < rows_) iterator = num_of_rows;
    for (int i = 0; i < iterator; i++)
      for (int j = 0; j < cols_; j++) tmp_mat[i][j] = matrix_[i][j];
    // Deallocating previous matrix
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
    // Assigning new matrix to previous one
    matrix_ = tmp_mat;
    rows_ = num_of_rows;
  }
}

void S21Matrix::set_num_of_cols(int num_of_cols) {
  if (num_of_cols) {
    double** tmp_mat = new double*[rows_];
    for (int i = 0; i < rows_; i++) tmp_mat[i] = new double[num_of_cols]();
    int iterator = cols_;
    if (num_of_cols < cols_) iterator = num_of_cols;
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < iterator; j++) tmp_mat[i][j] = matrix_[i][j];
    // Deallocating previous matrix
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
    // Assigning new matrix to previous one
    matrix_ = tmp_mat;
    cols_ = num_of_cols;
  }
}
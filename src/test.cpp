#include <gtest/gtest.h>

#include <stdexcept>

#include "s21_matrix_oop.h"

TEST(Constructor, def_const) {
  S21Matrix test_mat;
  EXPECT_EQ(3, test_mat.get_num_of_rows());
  EXPECT_EQ(3, test_mat.get_num_of_columns());
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) EXPECT_DOUBLE_EQ(0, test_mat(i, j));
}

TEST(Constructor, sec_constr) {
  S21Matrix test_mat(3, 7);
  EXPECT_EQ(3, test_mat.get_num_of_rows());
  EXPECT_EQ(7, test_mat.get_num_of_columns());
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 7; j++) EXPECT_DOUBLE_EQ(0, test_mat(i, j));
}

TEST(Constructor, third_constr) {
  S21Matrix test_mat(2, 2);
  test_mat[0][0] = 1;
  EXPECT_EQ(test_mat.get_num_of_rows(), 2);
  EXPECT_EQ(test_mat.get_num_of_columns(), 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      if (i == 0 and j == 0)
        EXPECT_DOUBLE_EQ(1, test_mat(i, j));
      else
        EXPECT_DOUBLE_EQ(0, test_mat(i, j));
  S21Matrix copy(test_mat);
  EXPECT_EQ(true, copy.EqMatrix(test_mat));
}

TEST(Constructor, last_constr) {
  S21Matrix tmp_mat(2, 5);
  S21Matrix test_mat(std::move(tmp_mat));
  EXPECT_EQ(tmp_mat.get_num_of_rows(), 0);
  EXPECT_EQ(tmp_mat.get_num_of_columns(), 0);
  EXPECT_EQ(test_mat.get_num_of_rows(), 2);
  EXPECT_EQ(test_mat.get_num_of_columns(), 5);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 5; j++) EXPECT_EQ(0, test_mat(i, j));
}

TEST(Destructor, dest_test) {
  S21Matrix test_mat(3, 4);
  test_mat.~S21Matrix();
  EXPECT_EQ(test_mat.get_num_of_rows(), 0);
  EXPECT_EQ(test_mat.get_num_of_columns(), 0);
}

TEST(Equality, equal) {
  S21Matrix mat1(2, 4);
  mat1[1][1] = -10;
  S21Matrix mat2(mat1);
  EXPECT_EQ(mat1.EqMatrix(mat2), true);
}

TEST(Equality, inequal) {
  S21Matrix mat1(2, 4);
  mat1[1][1] = -10;
  S21Matrix mat2(2, 4);
  EXPECT_EQ(mat1.EqMatrix(mat2), false);
}

TEST(Equality, wrong_dim) {
  S21Matrix mat1(2, 4);
  mat1[1][1] = -10;
  S21Matrix mat2(1, 4);
  EXPECT_EQ(mat1.EqMatrix(mat2), false);
}

TEST(Sum, correct) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  mat1.SumMatrix(mat2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(mat1(i, j), 3.35);
}

TEST(Sum, incorrect) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(3, 7);
  try {
    mat1.SumMatrix(mat2);
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(Sub, correct) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  mat1.SubMatrix(mat2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(mat1(i, j), -3.35);
}

TEST(Sub, incorrect) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(3, 7);
  try {
    mat1.SumMatrix(mat2);
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(MulNumber, mul_num_test) {
  S21Matrix mat(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat[i][j] = i + j;
  mat.MulNumber(2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_EQ(mat(i, j), 2 * (i + j));
}

TEST(MulMatrix, correct_dim) {
  S21Matrix mat1(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat1[i][j] = i + j;
  S21Matrix mat2(4, 2);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 2; j++) mat2[i][j] = i - j;
  mat1.MulMatrix(mat2);
  EXPECT_EQ(mat1.get_num_of_columns(), 2);
  EXPECT_EQ(mat1.get_num_of_rows(), 2);
  EXPECT_EQ(mat1(0, 0), 14);
  EXPECT_EQ(mat1(0, 1), 8);
  EXPECT_EQ(mat1(1, 0), 20);
  EXPECT_EQ(mat1(1, 1), 10);
}

TEST(MulMatrix, incorrect_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 2);
  try {
    mat1.MulMatrix(mat2);
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.",
        e.what());
  }
}

TEST(Transpose, tranp_test) {
  S21Matrix mat1(2, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) mat1[i][j] = i + j;
  S21Matrix mat2 = mat1.Transpose();
  EXPECT_EQ(mat2.get_num_of_rows(), 3);
  EXPECT_EQ(mat2.get_num_of_columns(), 2);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) EXPECT_EQ(mat2(i, j), mat1(j, i));
}

TEST(Determinant, correct_dimensions) {
  S21Matrix mat1(3, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) mat1[i][j] = i + j;
  double det = mat1.Determinant();
  EXPECT_DOUBLE_EQ(det, 0);
}

TEST(Determinant, incorrect_dims) {
  S21Matrix mat(2, 3);
  try {
    double det = mat.Determinant();
    det++;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "The matrix is not square.");
  }
}

TEST(AlgebraicAddition, correct_dim) {
  S21Matrix mat1(3, 3);
  mat1[0][0] = 1;
  mat1[0][1] = 2;
  mat1[0][2] = 3;
  mat1[1][0] = 0;
  mat1[1][1] = 4;
  mat1[1][2] = 2;
  mat1[2][0] = 5;
  mat1[2][1] = 2;
  mat1[2][2] = 1;
  S21Matrix complements = mat1.CalcComplements();
  EXPECT_EQ(complements.get_num_of_rows(), 3);
  EXPECT_EQ(complements.get_num_of_columns(), 3);
  EXPECT_DOUBLE_EQ(complements(0, 0), 0);
  EXPECT_DOUBLE_EQ(complements(0, 1), 10);
  EXPECT_DOUBLE_EQ(complements(0, 2), -20);
  EXPECT_DOUBLE_EQ(complements(1, 0), 4);
  EXPECT_DOUBLE_EQ(complements(1, 1), -14);
  EXPECT_DOUBLE_EQ(complements(1, 2), 8);
  EXPECT_DOUBLE_EQ(complements(2, 0), -8);
  EXPECT_DOUBLE_EQ(complements(2, 1), -2);
  EXPECT_DOUBLE_EQ(complements(2, 2), 4);
}

TEST(AlegraicAddition, incorrect_dim) {
  S21Matrix mat(2, 3);
  try {
    S21Matrix res_mat = mat.CalcComplements();
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "The matrix is not square.");
  }
}

TEST(Inverse, correct_dims) {
  S21Matrix mat1(3, 3);
  mat1[0][0] = 2;
  mat1[0][1] = 5;
  mat1[0][2] = 7;
  mat1[1][0] = 6;
  mat1[1][1] = 3;
  mat1[1][2] = 4;
  mat1[2][0] = 5;
  mat1[2][1] = -2;
  mat1[2][2] = -3;
  S21Matrix inv = mat1.InverseMatrix();
  EXPECT_EQ(inv.get_num_of_rows(), 3);
  EXPECT_EQ(inv.get_num_of_columns(), 3);
  EXPECT_DOUBLE_EQ(inv(0, 0), 1);
  EXPECT_DOUBLE_EQ(inv(0, 1), -1);
  EXPECT_DOUBLE_EQ(inv(0, 2), 1);
  EXPECT_DOUBLE_EQ(inv(1, 0), -38);
  EXPECT_DOUBLE_EQ(inv(1, 1), 41);
  EXPECT_DOUBLE_EQ(inv(1, 2), -34);
  EXPECT_DOUBLE_EQ(inv(2, 0), 27);
  EXPECT_DOUBLE_EQ(inv(2, 1), -29);
  EXPECT_DOUBLE_EQ(inv(2, 2), 24);
}

TEST(Inverse, zero_det) {
  S21Matrix mat1(3, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) mat1[i][j] = i + j;
  try {
    S21Matrix inv = mat1.InverseMatrix();
  } catch (const std::out_of_range& e) {
    EXPECT_STREQ(e.what(), "Matrix determinant is zero");
  }
}

TEST(Inverse, incorect_dim) {
  S21Matrix mat(1, 3);
  try {
    S21Matrix inv = mat.InverseMatrix();
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "The matrix is not square.");
  }
}

TEST(plus_operator, correct) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  S21Matrix res_mat = mat1 + mat2;
  EXPECT_EQ(res_mat.get_num_of_rows(), 2);
  EXPECT_EQ(res_mat.get_num_of_columns(), 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(res_mat(i, j), 3.35);
}

TEST(plus_operator, incorrect) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(3, 7);
  try {
    S21Matrix res_mat = mat1 + mat2;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(minus_operator, correct) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  S21Matrix res_mat = mat1 - mat2;
  EXPECT_EQ(res_mat.get_num_of_rows(), 2);
  EXPECT_EQ(res_mat.get_num_of_columns(), 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(res_mat(i, j), -3.35);
}

TEST(minus_operator, incorrect) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(3, 7);
  try {
    S21Matrix res_mat = mat1 - mat2;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(Mul_operator, correct_dim) {
  S21Matrix mat1(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat1[i][j] = i + j;
  S21Matrix mat2(4, 2);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 2; j++) mat2[i][j] = i - j;
  S21Matrix res_mat = mat1 * mat2;
  EXPECT_EQ(res_mat.get_num_of_columns(), 2);
  EXPECT_EQ(res_mat.get_num_of_rows(), 2);
  EXPECT_EQ(res_mat(0, 0), 14);
  EXPECT_EQ(res_mat(0, 1), 8);
  EXPECT_EQ(res_mat(1, 0), 20);
  EXPECT_EQ(res_mat(1, 1), 10);
}

TEST(Mul_operator, incorrect_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 2);
  try {
    S21Matrix res_mat = mat1 * mat2;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.",
        e.what());
  }
}

TEST(Mul_operator, number_first) {
  S21Matrix mat(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat[i][j] = i + j;
  S21Matrix res_mat = 2 * mat;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_EQ(res_mat(i, j), 2 * (i + j));
}

TEST(Mul_operator, number_second) {
  S21Matrix mat(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat[i][j] = i + j;
  S21Matrix res_mat = mat * 2;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_EQ(res_mat(i, j), 2 * (i + j));
}

TEST(equality_operator, equal) {
  S21Matrix mat1(2, 4);
  mat1[1][1] = -10;
  S21Matrix mat2(mat1);
  EXPECT_EQ(mat1 == mat2, true);
}

TEST(equality_operator, inequal) {
  S21Matrix mat1(2, 4);
  mat1[1][1] = -10;
  S21Matrix mat2(2, 4);
  EXPECT_EQ(mat1 == mat2, false);
}

TEST(Assignment, ass_test) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2 = mat1;
  EXPECT_EQ(mat1 == mat2, true);
}

TEST(Plus_eq_oper, correct_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  mat1 += mat2;
  EXPECT_EQ(mat1.get_num_of_rows(), 2);
  EXPECT_EQ(mat1.get_num_of_columns(), 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(mat1(i, j), 3.35);
}

TEST(Plus_eq_oper, incorrect_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 1);
  try {
    mat1 += mat2;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(Minus_eq_oper, correct_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) mat2[i][j] = 3.35;
  mat1 -= mat2;
  EXPECT_EQ(mat1.get_num_of_rows(), 2);
  EXPECT_EQ(mat1.get_num_of_columns(), 4);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) EXPECT_DOUBLE_EQ(mat1(i, j), -3.35);
}

TEST(Minus_eq_oper, incorrect_dim) {
  S21Matrix mat1(2, 4);
  S21Matrix mat2(2, 1);
  try {
    mat1 -= mat2;
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "Different matrix dimensions");
  }
}

TEST(Mul_eq_oper, number) {
  S21Matrix mat1(2, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) mat1[i][j] = 1;
  mat1 *= 2;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) EXPECT_DOUBLE_EQ(mat1(i, j), 2);
}

TEST(Mul_eq_oper, matrix) {
  S21Matrix mat1(2, 3);
  S21Matrix mat2(3, 2);
  mat1 *= mat2;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) EXPECT_DOUBLE_EQ(mat1(i, j), 0);
}

TEST(Index, incorrect_index) {
  S21Matrix mat;
  try {
    mat(4, 2);
  } catch (const std::out_of_range& e) {
    EXPECT_STREQ(e.what(), "Index is outside the matrix.");
  }
}

TEST(Setter, correct) {
  S21Matrix mat;
  mat.set_num_of_rows(7);
  mat.set_num_of_cols(2);
  EXPECT_EQ(mat.get_num_of_rows(), 7);
  EXPECT_EQ(mat.get_num_of_columns(), 2);
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 2; j++) EXPECT_DOUBLE_EQ(mat(i, j), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

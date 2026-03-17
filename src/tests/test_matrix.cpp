#include <gtest/gtest.h>

#include "../my_matrix_oop.cpp"

using namespace std;

TEST(MatrixTest, ConstructorSize) {
  myMatrix m_0(3, 4);
  EXPECT_EQ(m_0.get_rows(), 3);
  EXPECT_EQ(m_0.get_cols(), 4);

  EXPECT_THROW(myMatrix m_1(0, 0), const char *);
}

TEST(MatrixTest, CopyConstructor) {
  myMatrix m, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  myMatrix B(A);

  EXPECT_EQ(B.get_rows(), 2);
  EXPECT_EQ(B.get_cols(), 2);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  EXPECT_NE(A.get_matrix_(), B.get_matrix_());

  EXPECT_THROW(myMatrix m_4(m), const char *);
}

TEST(MatrixTest, MoveConstructor) {
  myMatrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  myMatrix B(move(A));

  EXPECT_EQ(B.get_rows(), 2);
  EXPECT_EQ(B.get_cols(), 2);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  EXPECT_EQ(A.get_matrix_(), nullptr);
}

TEST(MatrixTest, set_values) {
  myMatrix m, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  EXPECT_THROW(m.set_cols(1), const char *);
  EXPECT_THROW(m.set_rows(1), const char *);

  m.set_rows_cols(2, 2);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);

  A.set_rows_cols(3, 3);
  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(0, 2), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 2), 0);

  A.set_rows_cols(1, 1);
  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_THROW(A(1, 1), const char *);
}

TEST(MatrixTest, EqMatrix) {
  myMatrix m, n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  myMatrix B(A);
  EXPECT_TRUE(B.EqMatrix(A));

  A(0, 0) = 1.00000000004;
  EXPECT_TRUE(B.EqMatrix(A));

  A(0, 0) = 1.0000004;
  EXPECT_FALSE(B.EqMatrix(A));

  A(1, 1) = 4;
  A.set_rows_cols(3, 3);
  EXPECT_FALSE(B.EqMatrix(A));

  EXPECT_TRUE(n.EqMatrix(m));
  EXPECT_FALSE(B.EqMatrix(n));
}

TEST(MatrixTest, SumMatrix) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A.SumMatrix(B);

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A.SumMatrix(A);

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A.SumMatrix(B), const char *);
  EXPECT_NO_THROW(n.SumMatrix(m));
}

TEST(MatrixTest, SubMatrix) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A.SubMatrix(B);

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A.SubMatrix(A);

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A.SumMatrix(B), const char *);
  EXPECT_NO_THROW(n.SumMatrix(m));
}

TEST(MatrixTest, MulNumber) {
  myMatrix n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A.MulNumber(2);

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  A.MulNumber(0);

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  EXPECT_NO_THROW(n.MulNumber(2));
}

TEST(MatrixTest, MulMatrix) {
  myMatrix n, m, A(2, 2), B(2, 2), D(3, 3);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 2;
  B(0, 1) = 0;
  B(1, 0) = 1;
  B(1, 1) = 2;

  A.MulMatrix(B);
  EXPECT_DOUBLE_EQ(A(0, 0), 4);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 10);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_THROW(A.MulMatrix(D), const char *);

  B.set_cols(3);
  A.MulMatrix(B);
  EXPECT_DOUBLE_EQ(A(0, 0), 12);
  EXPECT_DOUBLE_EQ(A(0, 1), 8);
  EXPECT_DOUBLE_EQ(A(0, 2), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 28);
  EXPECT_DOUBLE_EQ(A(1, 1), 16);
  EXPECT_DOUBLE_EQ(A(1, 2), 0);

  EXPECT_NO_THROW(n.MulMatrix(m));
}

TEST(MatrixTest, Transpose) {
  myMatrix n, A(2, 2), B;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B = A.Transpose();

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 1), 3);
  EXPECT_DOUBLE_EQ(B(1, 0), 2);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  EXPECT_NO_THROW(n.Transpose());
}

TEST(MatrixTest, CalcComplements) {
  myMatrix n, A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  myMatrix B = A.CalcComplements();

  EXPECT_DOUBLE_EQ(B(0, 0), 0);
  EXPECT_DOUBLE_EQ(B(0, 1), 10);
  EXPECT_DOUBLE_EQ(B(0, 2), -20);
  EXPECT_DOUBLE_EQ(B(1, 0), 4);
  EXPECT_DOUBLE_EQ(B(1, 1), -14);
  EXPECT_DOUBLE_EQ(B(1, 2), 8);
  EXPECT_DOUBLE_EQ(B(2, 0), -8);
  EXPECT_DOUBLE_EQ(B(2, 1), -2);
  EXPECT_DOUBLE_EQ(B(2, 2), 4);

  A.set_cols(4);
  EXPECT_THROW(A.CalcComplements(), const char *);
  EXPECT_NO_THROW(n.CalcComplements());

  A.set_rows_cols(1, 1);
  myMatrix C = A.CalcComplements();
  EXPECT_DOUBLE_EQ(C(0, 0), 1);
}

TEST(MatrixTest, Determinant) {
  myMatrix n, A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  EXPECT_DOUBLE_EQ(A.Determinant(), -40);

  A.set_rows_cols(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  EXPECT_DOUBLE_EQ(A.Determinant(), -2);

  A.set_rows_cols(1, 1);
  EXPECT_DOUBLE_EQ(A.Determinant(), 1);

  A.set_cols(2);
  EXPECT_THROW(A.Determinant(), const char *);

  EXPECT_NO_THROW(n.Determinant());
}

TEST(MatrixTest, CalcComplementsNewMatrix) {
  myMatrix A(3, 3), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  A.CalcComplements_new_matrix(&B, 0, 1);

  EXPECT_DOUBLE_EQ(B(0, 0), 4);
  EXPECT_DOUBLE_EQ(B(0, 1), 6);
  EXPECT_DOUBLE_EQ(B(1, 0), 7);
  EXPECT_DOUBLE_EQ(B(1, 1), 9);

  A.CalcComplements_new_matrix(&B, 1, 0);

  EXPECT_DOUBLE_EQ(B(0, 0), 2);
  EXPECT_DOUBLE_EQ(B(0, 1), 3);
  EXPECT_DOUBLE_EQ(B(1, 0), 8);
  EXPECT_DOUBLE_EQ(B(1, 1), 9);
}

TEST(MatrixTest, sort_matrix) {
  myMatrix A(3, 3);
  A(0, 0) = 0;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 1;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 4;
  A(2, 1) = 8;
  A(2, 2) = 9;

  double sign = 1.0;
  A.sort_matrix(&A, &sign, 0);

  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(sign, -1.0);

  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(2, 0), 4);
}

TEST(MatrixTest, InverseMatrix) {
  myMatrix A(2, 2), C(2, 2);
  A(0, 0) = 4;
  A(0, 1) = 7;
  A(1, 0) = 2;
  A(1, 1) = 6;

  myMatrix B = A.InverseMatrix();

  EXPECT_DOUBLE_EQ(B(0, 0), 0.6);
  EXPECT_DOUBLE_EQ(B(0, 1), -0.7);
  EXPECT_DOUBLE_EQ(B(1, 0), -0.2);
  EXPECT_DOUBLE_EQ(B(1, 1), 0.4);

  EXPECT_THROW(C.InverseMatrix(), const char *);

  myMatrix D(A);
  D.set_cols(3);
  EXPECT_THROW(D.InverseMatrix(), const char *);
}

TEST(MatrixTest, operator_sum_eq) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A += B;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A += A;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A += B, const char *);
  EXPECT_NO_THROW(n += m);
}

TEST(MatrixTest, operator_sub_eq) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A -= B;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A -= A;

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A -= B, const char *);
  EXPECT_NO_THROW(n -= m);
}

TEST(MatrixTest, operator_MulNumber) {
  myMatrix n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A *= 2;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  A *= 0;

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  EXPECT_NO_THROW(n *= 2);
}

TEST(MatrixTest, operator_MulMatrix) {
  myMatrix n, m, A(2, 2), B(2, 2), D(3, 3);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 2;
  B(0, 1) = 0;
  B(1, 0) = 1;
  B(1, 1) = 2;

  A *= B;
  EXPECT_DOUBLE_EQ(A(0, 0), 4);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 10);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_THROW(A *= D, const char *);

  B.set_cols(3);
  A *= B;
  EXPECT_DOUBLE_EQ(A(0, 0), 12);
  EXPECT_DOUBLE_EQ(A(0, 1), 8);
  EXPECT_DOUBLE_EQ(A(0, 2), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 28);
  EXPECT_DOUBLE_EQ(A(1, 1), 16);
  EXPECT_DOUBLE_EQ(A(1, 2), 0);

  EXPECT_NO_THROW(n *= m);
}

TEST(MatrixTest, operator_sum) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A = A + B;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A = A + A;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A = A + B, const char *);
  EXPECT_THROW(n = n + m, const char *);
}

TEST(MatrixTest, operator_sub) {
  myMatrix n, m, A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A = A - B;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  A = A - A;

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  B.set_rows_cols(3, 3);
  EXPECT_THROW(A = A - B, const char *);
  EXPECT_THROW(n = n - m, const char *);
}

TEST(MatrixTest, operator_MulNumber_) {
  myMatrix n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  A = A * 2;

  EXPECT_DOUBLE_EQ(A(0, 0), 2);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 6);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  A = A * 0;

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0);

  EXPECT_THROW(n = n * 2, const char *);
}

TEST(MatrixTest, operator_MulMatrix_) {
  myMatrix n, m, A(2, 2), B(2, 2), D(3, 3);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 2;
  B(0, 1) = 0;
  B(1, 0) = 1;
  B(1, 1) = 2;

  A = A * B;
  EXPECT_DOUBLE_EQ(A(0, 0), 4);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 10);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);

  EXPECT_THROW(A = A * D, const char *);

  B.set_cols(3);
  A = A * B;
  EXPECT_DOUBLE_EQ(A(0, 0), 12);
  EXPECT_DOUBLE_EQ(A(0, 1), 8);
  EXPECT_DOUBLE_EQ(A(0, 2), 0);
  EXPECT_DOUBLE_EQ(A(1, 0), 28);
  EXPECT_DOUBLE_EQ(A(1, 1), 16);
  EXPECT_DOUBLE_EQ(A(1, 2), 0);

  EXPECT_THROW(n = n * m, const char *);
}

TEST(MatrixTest, operator_get_value) {
  myMatrix n, A(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(A(0, 1), 2);
  EXPECT_DOUBLE_EQ(A(1, 0), 3);
  EXPECT_DOUBLE_EQ(A(1, 1), 4);

  EXPECT_THROW(A(1, 2), const char *);
  EXPECT_THROW(n(0, 0), const char *);
}

TEST(MatrixTest, operator_EqMatrix) {
  myMatrix m, n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  myMatrix B(A);
  EXPECT_TRUE(B == A);

  A(0, 0) = 1.00000000004;
  EXPECT_TRUE(B == A);

  A(0, 0) = 1.0000004;
  EXPECT_FALSE(B == A);

  A(1, 1) = 4;
  A.set_rows_cols(3, 3);
  EXPECT_FALSE(B == A);

  EXPECT_TRUE(n == m);
  EXPECT_FALSE(B == n);
}

TEST(MatrixTest, Copy_operator) {
  myMatrix m, n, A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  myMatrix B = A;

  EXPECT_EQ(B.get_rows(), 2);
  EXPECT_EQ(B.get_cols(), 2);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  EXPECT_NE(A.get_matrix_(), B.get_matrix_());

  EXPECT_NO_THROW(n = m);
}

TEST(MatrixTest, Move_operator) {
  myMatrix A(2, 2), B, n, m;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B = (move(A));

  EXPECT_EQ(B.get_rows(), 2);
  EXPECT_EQ(B.get_cols(), 2);

  EXPECT_DOUBLE_EQ(B(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(1, 1), 4);

  EXPECT_EQ(A.get_matrix_(), nullptr);
  EXPECT_NO_THROW(n = (move(m)));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
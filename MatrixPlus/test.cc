#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Methods, EqMatrix) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 0;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  EXPECT_EQ(true, a.EqMatrix(b));
  b(2, 2) = 14;
  EXPECT_EQ(false, a.EqMatrix(b));
  S21Matrix c(3, 2);
  S21Matrix d(3, 3);
  EXPECT_EQ(false, c.EqMatrix(d));
}

TEST(Methods, SumMatrix) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  a.SumMatrix(b);
  EXPECT_EQ(a(2, 2), 26);
  EXPECT_EQ(0, a(0, 0));
  EXPECT_EQ(1, a(0, 1));
}

TEST(Methods, SubMatrix) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  b.SubMatrix(a);
  EXPECT_EQ(b(2, 2), 0);
  EXPECT_EQ(0, b(0, 0));
  EXPECT_EQ(-1, b(0, 1));
}

TEST(Methods, MulNumber) {
  S21Matrix a(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  a.MulNumber(3);
  EXPECT_EQ(a(2, 2), 39);
  EXPECT_EQ(0, a(0, 0));
  EXPECT_EQ(3, a(0, 1));
}

TEST(Methods, MulMatrix) {
  S21Matrix a(1, 3);
  S21Matrix b(3, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  b(0, 0) = 1;
  b(1, 0) = 1;
  b(2, 0) = 1;
  a.MulMatrix(b);
  double res = a(0, 0);
  EXPECT_EQ(res, 6);
  EXPECT_EQ(a.GetCols(), 1);
  EXPECT_EQ(a.GetRows(), 1);
}

TEST(Methods, Transpose) {
  S21Matrix a(1, 3);
  S21Matrix b;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  b = a.Transpose();
  EXPECT_EQ(b(0, 0), 1);
  EXPECT_EQ(b(1, 0), 2);
  EXPECT_EQ(b(2, 0), 3);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 1);
}

TEST(Methods, CalcComplements) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 4;
  a(1, 0) = 3;
  a(1, 1) = 3;
  a(1, 2) = 5;
  a(2, 0) = 2;
  a(2, 1) = 4;
  a(2, 2) = 4;
  b = a.CalcComplements();
  EXPECT_EQ(b(0, 0), -8);
  EXPECT_EQ(b(0, 1), -2);
  EXPECT_EQ(b(0, 2), 6);
  EXPECT_EQ(b(1, 0), 8);
  EXPECT_EQ(b(1, 1), -4);
  EXPECT_EQ(b(1, 2), 0);
  EXPECT_EQ(b(2, 0), -2);
  EXPECT_EQ(b(2, 1), 7);
  EXPECT_EQ(b(2, 2), -3);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 3);
}

TEST(Methods, Determinant) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 4;
  a(1, 0) = 3;
  a(1, 1) = 3;
  a(1, 2) = 5;
  a(2, 0) = 2;
  a(2, 1) = 4;
  a(2, 2) = 4;
  double res = a.Determinant();
  EXPECT_EQ(res, 12);
  S21Matrix b;
  b(0, 0) = 14;
  res = b.Determinant();
  EXPECT_EQ(res, 14);
}

TEST(Methods, InverseMatrix) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  S21Matrix b(2, 2);
  b = a.InverseMatrix();
  EXPECT_EQ(b(0, 0), -2);
  EXPECT_EQ(b(0, 1), 1);
  EXPECT_EQ(b(1, 0), 1.5);
  EXPECT_EQ(b(1, 1), -0.5);
  S21Matrix c;
  c(0, 0) = 2;
  S21Matrix d;
  d = c.InverseMatrix();
  EXPECT_EQ(d(0, 0), 0.5);
}

TEST(Operators, Sum) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  S21Matrix c(3, 3);
  c = a + b;
  EXPECT_EQ(c(2, 2), 26);
  EXPECT_EQ(0, c(0, 0));
  EXPECT_EQ(1, c(0, 1));
}

TEST(Operators, Sub) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  S21Matrix c(3, 3);
  c = b - a;
  EXPECT_EQ(c(2, 2), 0);
  EXPECT_EQ(0, c(0, 0));
  EXPECT_EQ(-1, c(0, 1));
}

TEST(Operators, Eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 1;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 13;
  EXPECT_TRUE(a == b);
  b(0, 1) = 25;
  EXPECT_EQ(0, a == b);
}

TEST(Operators, Equating) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 47;
  a = b;
  EXPECT_EQ(a(2, 2), 47);
  EXPECT_EQ(0, a(0, 1));
}

TEST(Operators, EquatingSum) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 47;
  a += b;
  EXPECT_EQ(a(2, 2), 60);
  EXPECT_EQ(1, a(0, 1));
}

TEST(Operators, EquatingSub) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;
  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;
  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 47;
  a -= b;
  EXPECT_EQ(a(2, 2), -34);
  EXPECT_EQ(1, a(0, 1));
}

TEST(Operators, EquatingMulNumber) {
  S21Matrix a(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(0, 2) = 0;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 0;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 13;
  a *= -3;
  EXPECT_EQ(a(2, 2), -39);
  EXPECT_EQ(-3, a(0, 1));
}

TEST(Operators, EquatingMulMatrix) {
  S21Matrix a(1, 3);
  S21Matrix b(3, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  b(0, 0) = 1;
  b(1, 0) = 1;
  b(2, 0) = 1;
  a *= b;
  EXPECT_EQ(a(0, 0), 6);
  EXPECT_EQ(a.GetCols(), 1);
  EXPECT_EQ(a.GetRows(), 1);
}

TEST(Operators, MulMatrix) {
  S21Matrix a(1, 3);
  S21Matrix b(3, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  b(0, 0) = 1;
  b(1, 0) = 1;
  b(2, 0) = 1;
  S21Matrix c;
  c = a * b;
  EXPECT_EQ(c(0, 0), 6);
  EXPECT_EQ(c.GetCols(), 1);
  EXPECT_EQ(c.GetRows(), 1);
}

TEST(Operators, MulMatrixByNumber) {
  S21Matrix a(1, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  S21Matrix c(1, 3);
  c = a * 3;
  EXPECT_EQ(c(0, 0), 3);
  EXPECT_EQ(c(0, 1), 6);
  EXPECT_EQ(c(0, 2), 9);
  c = -5 * a;
  EXPECT_EQ(c(0, 0), -5);
  EXPECT_EQ(c(0, 1), -10);
  EXPECT_EQ(c(0, 2), -15);
}

TEST(Operators, SetRowsCols) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  a.SetRows(4);
  a.SetCols(2);
  EXPECT_EQ(a(3, 0), 0);
  EXPECT_EQ(a(3, 1), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
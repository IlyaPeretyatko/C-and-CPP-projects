#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <cmath>
#include <cstdbool>
#include <cstdlib>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void AllocateMatrix();
  void DeleteMatrix() noexcept;
  double GetDeterminant(const S21Matrix& A) const noexcept;
  void GetMinor(const S21Matrix& A, int row, int column,
                S21Matrix* result) const noexcept;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  friend S21Matrix operator*(const S21Matrix& other, const double num) noexcept;
  friend S21Matrix operator*(const double num, const S21Matrix& other) noexcept;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix operator=(const S21Matrix& other) noexcept;
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const double num) noexcept;
  void operator*=(const S21Matrix& other);
  double& operator()(int i, int j);

  int GetCols() const noexcept;
  int GetRows() const noexcept;
  void SetCols(int cols);
  void SetRows(int rows);
};

#endif

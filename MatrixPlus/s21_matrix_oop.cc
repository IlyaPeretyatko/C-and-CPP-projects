#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) { AllocateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  AllocateMatrix();
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

S21Matrix::S21Matrix(S21Matrix&& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMatrix();
  for (int i = 0; i < rows_; ++i) {
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_, matrix_[i]);
  }
}

// вспомогательные функции

void S21Matrix::DeleteMatrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      } else {
        break;
      }
    }
    delete[] matrix_;
  }
}

void S21Matrix::AllocateMatrix() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::exception();
  }
  matrix_ = new double*[rows_];
  if (matrix_ == nullptr) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    if (matrix_[i] == nullptr) {
      throw std::exception();
    }
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

double S21Matrix::GetDeterminant(const S21Matrix& A) const noexcept {
  double determinant = 0;
  if (A.rows_ == 1) {
    determinant = A.matrix_[0][0];
  } else {
    determinant =
        A.matrix_[0][0] * A.matrix_[1][1] - A.matrix_[0][1] * A.matrix_[1][0];
  }
  return determinant;
}

void S21Matrix::GetMinor(const S21Matrix& A, int row, int column,
                         S21Matrix* result) const noexcept {
  int i_res = 0;
  int j_res = 0;
  for (int i = 0; i < A.rows_; ++i) {
    for (int j = 0; j < A.cols_; ++j) {
      if (i != row && j != column) {
        result->matrix_[i_res][j_res] = A.matrix_[i][j];
        j_res++;
        if (j_res == result->cols_) {
          i_res++;
          j_res = 0;
        }
      }
    }
  }
}

// methods

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::exception();
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::exception();
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor(rows_ - 1, cols_ - 1);
        GetMinor(*this, i, j, &minor);
        double value_minor = minor.Determinant();
        if (value_minor == 0) {
          result.matrix_[i][j] = 0;
        } else {
          result.matrix_[i][j] = ((i + j + 2) % 2 == 0 ? 1 : -1) * value_minor;
        }
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  double result = 0;
  if (rows_ != cols_) {
    throw std::exception();
  }
  if (rows_ <= 2) {
    result = GetDeterminant(*this);
  } else {
    for (int i = 0; i < cols_; ++i) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      GetMinor(*this, 0, i, &minor);
      double value_minor = minor.Determinant();
      result += matrix_[0][i] * ((1 + i + 1) % 2 == 0 ? 1 : -1) * value_minor;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result(rows_, cols_);
  if (rows_ != 1) {
    double determinant = (*this).Determinant();
    if (fabs(determinant) >= 1e-7) {
      result = (*this).CalcComplements().Transpose();
      result.MulNumber(1 / determinant);
    } else {
      throw std::exception();
    }
  } else {
    if ((*this).matrix_[0][0] != 0) {
      result.matrix_[0][0] = 1 / (*this).matrix_[0][0];
    }
  }
  return result;
}

// перегрузка операторов

S21Matrix S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this == &other) {
    return *this;
  }
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMatrix();
  for (int i = 0; i < rows_; ++i) {
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_, matrix_[i]);
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  S21Matrix result((*this));
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  S21Matrix result((*this));
  result.SubMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return 0;
  }
  return (*this).EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { (*this).SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { (*this).SubMatrix(other); }

void S21Matrix::operator*=(const double num) noexcept {
  (*this).MulNumber(num);
}

void S21Matrix::operator*=(const S21Matrix& other) { (*this).MulMatrix(other); }

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix operator*(const S21Matrix& other, const double num) noexcept {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) noexcept {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::exception();
  }
  return matrix_[i][j];
}

// аксесоры и мутаторы

int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::exception();
  }
  if (cols != cols_) {
    S21Matrix tmp(rows_, cols);
    int min = std::min(cols_, cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = tmp;
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::exception();
  }
  if (rows != rows_) {
    S21Matrix tmp{rows, cols_};
    int min = std::min(rows_, rows);
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = tmp;
  }
}

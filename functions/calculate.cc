#include "../s21_matrix_oop.h"

// If matrix A == matrix B
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool code = true;
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    code = false;
  }
  for (int i = 0; i < this->rows_ && code == true; i++) {
    for (int j = 0; j < this->cols_ && code == true; j++) {
      if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        code = false;
      }
    }
  }

  return code;
}

// Sum 2 matrices: A+B
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw VoidErr();
  } else if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw SumErr();
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Sub 2 matrices: A-B
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw VoidErr();
  } else if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw SubErr();
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Matrix multiplication by scalar: A * n
void S21Matrix::MulNumber(const double num) {
  if (this->matrix_ == nullptr) {
    throw VoidErr();
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

// Multiplication of two matrices: A * B
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw VoidErr();
  } else if (this->cols_ != other.rows_) {
    throw MultErr();
  }

  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->SetCols(result.cols_);
  this->Move(result);
}

// Return transposed matrix
S21Matrix S21Matrix::Transpose() {
  if (this->matrix_ == nullptr) {
    throw VoidErr();
  }
  S21Matrix transposed(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      transposed.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return transposed;
}

// Determinant for matrix 2x2
double S21Matrix::Det2() noexcept {
  return this->matrix_[0][0] * this->matrix_[1][1] -
         this->matrix_[0][1] * this->matrix_[1][0];
}

// Returns matrix without n-th row and m-th col
S21Matrix S21Matrix::CrossOut(int n, int m) {
  S21Matrix crossed(this->rows_ - 1, this->cols_ - 1);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (j < m && i < n) {
        crossed.matrix_[i][j] = this->matrix_[i][j];
      } else if (j < m && i > n) {
        crossed.matrix_[i - 1][j] = this->matrix_[i][j];
      } else if (j > m && i < n) {
        crossed.matrix_[i][j - 1] = this->matrix_[i][j];
      } else if (j > m && i > n) {
        crossed.matrix_[i - 1][j - 1] = this->matrix_[i][j];
      }
    }
  }
  return crossed;
}

// Determinant of custom matrix
double S21Matrix::Determinant() {
  if (this->cols_ != this->rows_) {
    throw DetermErr();
  } else if (this->matrix_ == nullptr) {
    throw VoidErr();
  }

  double result = 0;

  if (this->cols_ == 1) {
    result = this->matrix_[0][0];
  } else if (this->cols_ == 2) {
    result = this->Det2();
  } else {
    for (int i = 0; i < this->rows_; i++) {
      S21Matrix B = this->CrossOut(i, 0);
      double temp_result = B.Determinant();
      result += pow(-1, i + 2) * this->matrix_[i][0] * temp_result;
    }
  }
  return result;
}

//
S21Matrix S21Matrix::CalcComplements() {
  if (this->cols_ != this->rows_ || this->cols_ == 1) {
    throw ComplementErr();
  } else if (this->matrix_ == nullptr) {
    throw VoidErr();
  }
  S21Matrix result(this->rows_, this->cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      S21Matrix B = this->CrossOut(i, j);
      result.matrix_[i][j] = B.Determinant();
      result.matrix_[i][j] *= pow(-1, i + j + 2);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->cols_ != this->rows_) {
    throw InverseErr("Inverse matrix: the matrix is not square");
  } else if (this->matrix_ == nullptr) {
    throw VoidErr();
  } else if (this->rows_ < 2) {
    throw InverseErr("Inverse matrix: size of matrix is < 2x2");
  }
  double determ = this->Determinant();
  if (determ == 0) {
    throw InverseErr("Inverse matrix: determinant of matrix is 0");
  }

  S21Matrix complement = this->CalcComplements();
  S21Matrix transposed = complement.Transpose();
  transposed.MulNumber((double)1 / determ);
  return transposed;
}
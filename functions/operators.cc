#include "../s21_matrix_oop.h"

// Return address of matrix index (can change its value)
double& S21Matrix::operator()(int row, int col) {
  if (this->matrix_ == nullptr) {
    throw VoidErr();
  } else if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw RangeErr();
  }
  return matrix_[row][col];
}

// Return value of matrix index (can't change it)
// double S21Matrix::operator()(int row, int col) const {
//   if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
//     throw out_of_range("Index is out of range");
//   }
//   return matrix_[row][col];
// }

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.SumMatrix(o);
  return copy;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.SubMatrix(o);
  return copy;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.MulMatrix(o);
  return copy;
}

S21Matrix operator*(double num, const S21Matrix& o) {
  S21Matrix copy(o);
  copy.MulNumber(num);
  return copy;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix copy(*this);
  copy.MulNumber(num);
  return copy;
}

bool S21Matrix::operator==(const S21Matrix& o) { return this->EqMatrix(o); }

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (&o != this) {
    S21Matrix copy(o);
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    this->rows_ = copy.rows_;
    this->cols_ = copy.cols_;
    this->Alloc();
    this->Move(copy);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.SumMatrix(o);
  this->Move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.SubMatrix(o);
  this->Move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  S21Matrix copy(*this);
  copy.MulMatrix(o);
  this->SetCols(copy.cols_);
  this->Move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  S21Matrix copy(*this);
  copy.MulNumber(num);
  this->Move(copy);
  return *this;
}
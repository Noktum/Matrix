#include "../s21_matrix_oop.h"

/* Constructors and destructor */

void S21Matrix::Alloc() {
  this->matrix_ = new (nothrow) double*[rows_];  // if except, then

  if (this->matrix_ == nullptr) {
    this->cols_ = 0;
    this->rows_ = 0;
    delete[] this->matrix_;
    throw AllocErr();
  }

  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new (nothrow) double[cols_]();
    if (this->matrix_[i] == nullptr) {
      this->cols_ = 0;
      this->rows_ = 0;
      for (int j = 0; j < i; j++) {
        delete[] this->matrix_[j];
      }
      delete[] this->matrix_;
      this->matrix_ = nullptr;
      throw AllocErr();
    }
  }
}

// Default constructor for custom matrix
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    this->rows_ = 0;
    this->cols_ = 0;
    throw MatrixException();
  }
  this->Alloc();
}

// Constructor with no parameters for void matrix
S21Matrix::S21Matrix() {}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) {
  if (other.matrix_ == nullptr) {
    throw VoidErr();
  }
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->Alloc();
  this->Move(other);
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (other.matrix_ == nullptr) {
    throw VoidErr();
  }
  if (this != &other) {
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
}

// Destructor
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
  }
  this->matrix_ = nullptr;
}

void S21Matrix::Move(const S21Matrix& other) {
  int rows = this->rows_, cols = this->cols_;
  if (this->cols_ > other.cols_) {
    cols = other.cols_;
  }
  if (this->rows_ > other.rows_) {
    rows = other.rows_;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::GetRows() { return this->rows_; }

int S21Matrix::GetCols() { return this->cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw MatrixException("Rows value is less than 1");
  }
  S21Matrix copy(*this);
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->rows_ = rows;
  this->Alloc();
  this->Move(copy);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw MatrixException("Cols value is less than 1");
  }
  S21Matrix copy(*this);
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->cols_ = cols;
  this->Alloc();
  this->Move(copy);
}

// void S21Matrix::Print() {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_ - 1; j++) {
//       cout << matrix_[i][j] << " ";
//     }
//     cout << matrix_[i][cols_ - 1] << "\n";
//   }
// }

// void S21Matrix::Input() {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       cin >> matrix_[i][j];
//     }
//   }
// }
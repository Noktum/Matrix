#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#include <cmath>
#include <cstring>
#include <exception>
#include <iostream>
#include <new>

#define EPS 1e-7
using namespace std;

class S21Matrix {
  friend S21Matrix operator*(double num, const S21Matrix& o);

 private:
  int rows_ = 0, cols_ = 0;  // Rows and columns
  double** matrix_ =
      nullptr;  // Pointer to the memory where the matrix is allocated

  double Det2() noexcept;  // Determinant for matrix 2x2
  void Alloc();
  S21Matrix CrossOut(int n, int m);
  void Move(const S21Matrix& other);  // Copy matrix_ to "this"

 public:
  // void Print();
  // void Input();

  S21Matrix();   // Default constructor for matrix 2x2
  ~S21Matrix();  // Destructor

  S21Matrix(int rows, int cols);      // Constructor for custom matrix
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor

  int GetRows(), GetCols();
  void SetRows(int rows), SetCols(int cols);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators overloads
  double& operator()(int row, int col);
  // double operator()(int row, int col) const;

  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix operator*(double num);

  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(double num);

  bool operator==(const S21Matrix& o);
};

/* Exceptions classes */
class MatrixException {
 private:
  string message = "Matrix constructor: invalid value in rows or columns";

 public:
  MatrixException() {}
  explicit MatrixException(const string& msg) : message(msg) {}
  string what() const { return message; }
};

class VoidErr : public MatrixException {
 public:
  VoidErr() : MatrixException("Used matrix is NULL") {}
};

class AllocErr : public MatrixException {
 public:
  AllocErr() : MatrixException("Matrix constructor: allocation error") {}
};

class SumErr : public MatrixException {
 public:
  SumErr() : MatrixException("Matrix sum: different matrix dimensions") {}
};

class SubErr : public MatrixException {
 public:
  SubErr() : MatrixException("Matrix substract: different matrix dimensions") {}
};

class MultErr : public MatrixException {
 public:
  MultErr()
      : MatrixException(
            "Matrix multiplication: the number of columns of the 1st matrix is "
            "not equal to the number of rows of the 2nd one.") {}
};

class DetermErr : public MatrixException {
 public:
  DetermErr() : MatrixException("Determinant: the matrix is not square") {}
};

class ComplementErr : public MatrixException {
 public:
  ComplementErr()
      : MatrixException(
            "Algebraic addition: the matrix is not square or its size < 2x2") {}
};

class InverseErr : public MatrixException {
 public:
  explicit InverseErr(const string& msg) : MatrixException(msg) {}
};

class RangeErr : public MatrixException {
 public:
  RangeErr() : MatrixException("Index is out of range") {}
};

#endif  // !S21_MATRIX

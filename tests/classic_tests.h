#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(constructor, small_sizes) {
  for (int i = 1; i < 10; i++) {
    S21Matrix a(i, i);
    EXPECT_EQ(i, a.GetCols());
    EXPECT_EQ(i, a.GetRows());
  }
}

TEST(constructor, memtest) {
  for (int i = 21474830; i < 21474835; i++) {
    try {
      S21Matrix a(1, i);
    } catch (const AllocErr& e) {
      std::cerr << e.what() << '\n';
    }
  }
}

TEST(constructor, except_rows) {
  for (int i = -5; i < 0; i++) {
    EXPECT_THROW(
        {
          try {
            S21Matrix a(i, 1);
          } catch (const MatrixException& e) {
            EXPECT_EQ("Matrix constructor: invalid value in rows or columns",
                      e.what());
            throw;
          }
        },
        MatrixException);
  }
}

TEST(constructor, except_cols) {
  for (int i = -5; i < 0; i++) {
    EXPECT_THROW(
        {
          try {
            S21Matrix a(1, i);
          } catch (const MatrixException& e) {
            EXPECT_EQ("Matrix constructor: invalid value in rows or columns",
                      e.what());
            throw;
          }
        },
        MatrixException);
  }
}

TEST(constructor, standart) {
  S21Matrix test;
  EXPECT_EQ(test.GetRows(), 0);
  EXPECT_EQ(test.GetCols(), 0);
}

TEST(constructor, copy) {
  S21Matrix orig(2, 3);
  int k = 0;
  for (int i = 0; i < orig.GetRows(); i++) {
    for (int j = 0; j < orig.GetCols(); j++) {
      orig(i, j) = k;
      k++;
    }
  }
  S21Matrix copy(orig);
  EXPECT_EQ(copy.GetRows(), orig.GetRows());
  EXPECT_EQ(copy.GetCols(), orig.GetCols());

  for (int i = 0; i < orig.GetRows(); i++) {
    for (int j = 0; j < orig.GetCols(); j++) {
      EXPECT_EQ(copy(i, j), orig(i, j));
    }
  }
}

TEST(constructor, copy_large) {
  int rows = 100;
  int cols = 100;
  S21Matrix orig(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      orig(i, j) = i * cols + j;
    }
  }

  S21Matrix copy(orig);

  EXPECT_EQ(copy.GetRows(), orig.GetRows());
  EXPECT_EQ(copy.GetCols(), orig.GetCols());

  for (int i = 0; i < orig.GetRows(); ++i) {
    for (int j = 0; j < orig.GetCols(); ++j) {
      EXPECT_EQ(copy(i, j), orig(i, j));
    }
  }
}

TEST(constructor, move) {
  int rows = 100;
  int cols = 100;
  S21Matrix orig(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      orig(i, j) = i * cols + j;
    }
  }
  S21Matrix copy(orig);
  S21Matrix moved(move(orig));

  EXPECT_EQ(orig.GetRows(), 0);
  EXPECT_EQ(orig.GetCols(), 0);
  EXPECT_EQ(true, moved.EqMatrix(copy));
}

TEST(constructor, copy_null) {
  S21Matrix test;

  EXPECT_THROW(
      {
        try {
          S21Matrix copy(test);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

TEST(constructor, move_null) {
  S21Matrix test;

  EXPECT_THROW(
      {
        try {
          S21Matrix copy(move(test));
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

TEST(setters, set_cols_0) {
  S21Matrix test(1, 1);

  EXPECT_THROW(
      {
        try {
          test.SetCols(0);
        } catch (const MatrixException& e) {
          EXPECT_EQ(e.what(), "Cols value is less than 1");
          throw;
        }
      },
      MatrixException);
}

TEST(setters, set_rows_0) {
  S21Matrix test(1, 1);

  EXPECT_THROW(
      {
        try {
          test.SetRows(0);
        } catch (const MatrixException& e) {
          EXPECT_EQ(e.what(), "Rows value is less than 1");
          throw;
        }
      },
      MatrixException);
}

TEST(setters, set_rows_less) {
  S21Matrix matrix1(2, 3), matrix2(1, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;

  matrix1.SetRows(1);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_rows_more) {
  S21Matrix matrix1(2, 3), matrix2(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.SetRows(3);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_cols_less) {
  S21Matrix matrix1(2, 3), matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  matrix1.SetCols(2);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_cols_more) {
  S21Matrix matrix1(2, 3), matrix2(2, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.SetCols(4);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}
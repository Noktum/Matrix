#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

// стандартное сложение
TEST(summarize, common) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 6);
  EXPECT_EQ(matrix1(0, 1), 8);
  EXPECT_EQ(matrix1(1, 0), 10);
  EXPECT_EQ(matrix1(1, 1), 12);
}

// проверка на исключение при разных размерах
TEST(summarize, diff_size) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(
      {
        try {
          matrix1.SumMatrix(matrix2);
        } catch (const SumErr& e) {
          EXPECT_EQ(e.what(), "Matrix sum: different matrix dimensions");
          throw;
        }
      },
      SumErr);
}

// проверка сложения через "обратные" значения
TEST(summarize, to_zero) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = -1;
  matrix2(0, 1) = -2;
  matrix2(1, 0) = -3;
  matrix2(1, 1) = -4;

  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1.EqMatrix(matrix3), true);
}

TEST(summarize, 1st_empty) {
  S21Matrix matrix1, matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  EXPECT_THROW(
      {
        try {
          matrix1.SumMatrix(matrix2);
        } catch (const MatrixException& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

/**********************************************************************************/

// сравнение пустых матриц
TEST(equal_test, empty) {
  S21Matrix matrix1, matrix2;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Тест на случай, если обе матрицы имеют одинаковые элементы
TEST(equal_test, same) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Тест на случай, если матрицы имеют разные размеры
TEST(equal_test, diff_size) {
  S21Matrix matrix1(2, 2), matrix2(3, 3);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Тест на случай, если матрицы имеют разные значения
TEST(equal_test, diff) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(matrix1);
  matrix2(1, 1) = 5;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Тест на случай, если одна матрица пустая, а другая нет
TEST(equal_test, one_empty) {
  S21Matrix matrix1, matrix2(2, 2);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

/********************************************************************************/

// Тест на умножение пустой матрицы на число
TEST(mul_number_test, null_exception) {
  S21Matrix matrix;

  EXPECT_THROW(
      {
        try {
          matrix.MulNumber(5);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тест на умножение матрицы с положительными значениями на положительное число
TEST(mul_number_test, common) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.MulNumber(2);

  EXPECT_EQ(matrix(0, 0), 2);
  EXPECT_EQ(matrix(0, 1), 4);
  EXPECT_EQ(matrix(1, 0), 6);
  EXPECT_EQ(matrix(1, 1), 8);
}

// Тест на умножение матрицы с отрицательными значениями на отрицательное число
TEST(mul_number_test, neg_mul_neg) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1;
  matrix(0, 1) = -2;
  matrix(1, 0) = -3;
  matrix(1, 1) = -4;

  matrix.MulNumber(-3);
  EXPECT_EQ(matrix(0, 0), 3);
  EXPECT_EQ(matrix(0, 1), 6);
  EXPECT_EQ(matrix(1, 0), 9);
  EXPECT_EQ(matrix(1, 1), 12);
}

// Тест на умножение матрицы с нулевыми значениями на число
TEST(mul_number_test, zero_matrix) {
  S21Matrix matrix(3, 3), matrix2(3, 3);
  matrix.MulNumber(10);
  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

// Тест на умножение матрицы на ноль
TEST(mul_number_test, mul_zero) {
  S21Matrix matrix(2, 2), matrix2(2, 2);

  matrix(0, 0) = 5;
  matrix(0, 1) = 6;
  matrix(1, 0) = 7;
  matrix(1, 1) = 8;

  matrix.MulNumber(0);
  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

// Тест на умножение матрицы с произвольными значениями на единицу
TEST(mul_number_test, mul_1) {
  S21Matrix matrix(2, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  S21Matrix matrix2(matrix);
  matrix.MulNumber(1);

  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

/****************************************************************************************/

// Тест на случай, если обе матрицы пустые
TEST(mul_matrix_test, both_empty) {
  S21Matrix matrix1, matrix2;

  EXPECT_THROW(
      {
        try {
          matrix1.MulMatrix(matrix2);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тест на случай, если первая матрица пустая, а вторая нет
TEST(mul_matrix_test, 1st_empty) {
  S21Matrix matrix1, matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  EXPECT_THROW(
      {
        try {
          matrix1.MulMatrix(matrix2);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тест на случай, если вторая матрица пустая, а первая нет
TEST(mul_matrix_test, 2nd_empty) {
  S21Matrix matrix1(2, 2), matrix2;

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  EXPECT_THROW(
      {
        try {
          matrix1.MulMatrix(matrix2);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тест на случай, если количество столбцов первой матрицы не равно количеству
// строк второй матрицы
TEST(mul_matrix_test, wrong_size) {
  S21Matrix matrix1(2, 3), matrix2(4, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;
  matrix2(3, 0) = 13;
  matrix2(3, 1) = 14;

  EXPECT_THROW(
      {
        try {
          matrix1.MulMatrix(matrix2);
        } catch (const MultErr& e) {
          EXPECT_EQ(
              e.what(),
              "Matrix multiplication: the number of columns of the 1st matrix "
              "is not equal to the number of rows of the 2nd one.");
          throw;
        }
      },
      MultErr);
}

// Тест на корректное умножение двух матриц
TEST(mul_matrix_test, common) {
  S21Matrix matrix1(2, 3), matrix2(3, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 1 * 7 + 2 * 9 + 3 * 11);
  EXPECT_EQ(matrix1(0, 1), 1 * 8 + 2 * 10 + 3 * 12);
  EXPECT_EQ(matrix1(1, 0), 4 * 7 + 5 * 9 + 6 * 11);
  EXPECT_EQ(matrix1(1, 1), 4 * 8 + 5 * 10 + 6 * 12);
}

// Тест на умножение матриц с нулями
TEST(mul_matrix_test, to_zero) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);  // 2x2 матрица

  matrix1(0, 0) = 0;
  matrix1(0, 1) = 0;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 0);
  EXPECT_EQ(matrix1(0, 1), 0);
  EXPECT_EQ(matrix1(1, 0), 1 * 3);
  EXPECT_EQ(matrix1(1, 1), 1 * 4);
}

/*********************************************************************************/

// Тестирование вычитания матриц разного размера
TEST(sub_matrix_test, diff_size) {
  S21Matrix matrix1(2, 2), matrix2(1, 1);

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;

  matrix2(0, 0) = 1;

  EXPECT_THROW(
      {
        try {
          matrix1.SubMatrix(matrix2);
        } catch (const SubErr& e) {
          EXPECT_EQ(e.what(), "Matrix substract: different matrix dimensions");
          throw;
        }
      },
      SubErr);
}

// Тестирование вычитания пустых матриц
TEST(sub_matrix_test, both_empty) {
  S21Matrix matrix1, matrix2;

  EXPECT_THROW(
      {
        try {
          matrix1.SubMatrix(matrix2);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тестирование вычитания матриц, одна из которых пустая
TEST(sub_matrix_test, one_empty) {
  S21Matrix matrix1(2, 2), matrix2;

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;

  EXPECT_THROW(
      {
        try {
          matrix1.SubMatrix(matrix2);
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тестирование вычитания матриц одного размера
TEST(sub_matrix_test, common) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 4);
  EXPECT_EQ(matrix1(0, 1), 2);
  EXPECT_EQ(matrix1(1, 0), 3);
  EXPECT_EQ(matrix1(1, 1), 1);
}

/********************************************************************/

// Тестирование транспонирования пустой матрицы
TEST(transpose, empty) {
  S21Matrix matrix;

  EXPECT_THROW(
      {
        try {
          S21Matrix result = matrix.Transpose();
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тестирование транспонирования матрицы 1x1
TEST(transpose, 1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_EQ(result(0, 0), 5);
}

// Тестирование транспонирования прямоугольной матрицы 2x3
TEST(transpose, rectangle) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(2, 1), 6);
}

// Тестирование транспонирования квадратной матрицы 3x3
TEST(transpose, square) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(0, 2), 7);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(1, 2), 8);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(2, 1), 6);
  EXPECT_EQ(result(2, 2), 9);
}

/************************************************************/

// Тестирование вычисления определителя для пустой матрицы
TEST(determ_test, empty) {
  S21Matrix matrix;
  EXPECT_THROW(
      {
        try {
          matrix.Determinant();
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тестирование вычисления определителя для прямоугольной матрицы (количество
// строк не равно количеству столбцов)
TEST(determ_test, not_square) {
  S21Matrix matrix(2, 3);  // Прямоугольная матрица
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  // Ожидается исключение, так как матрица не квадратная
  EXPECT_THROW(
      {
        try {
          matrix.Determinant();
        } catch (const DetermErr& e) {
          EXPECT_EQ(e.what(), "Determinant: the matrix is not square");
          throw;
        }
      },
      DetermErr);
}

// Тестирование вычисления определителя 1x1 матрицы
TEST(determ_test, 1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 7.0;

  // Определитель матрицы 1x1 равен элементу этой матрицы
  EXPECT_DOUBLE_EQ(matrix.Determinant(), 7.0);
}

// Тестирование вычисления определителя 2x2 матрицы
TEST(determ_test, 2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 1.0 * 4.0 - 2.0 * 3.0);
}

// Тестирование вычисления определителя 3x3 матрицы
TEST(determ_test, 3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double expected = 0.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), expected);
}

// Тестирование вычисления определителя 4x4 матрицы
TEST(determ_test, 4x4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(0, 3) = 4.0;
  matrix(1, 0) = 5.0;
  matrix(1, 1) = 6.0;
  matrix(1, 2) = 7.0;
  matrix(1, 3) = 8.0;
  matrix(2, 0) = 9.0;
  matrix(2, 1) = 10.0;
  matrix(2, 2) = 11.0;
  matrix(2, 3) = 12.0;
  matrix(3, 0) = 13.0;
  matrix(3, 1) = 14.0;
  matrix(3, 2) = 15.0;
  matrix(3, 3) = 16.0;

  double expected = 0.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), expected);
}

/***********************************************************************/

TEST(complement, empty) {
  S21Matrix matrix;

  EXPECT_THROW(
      {
        try {
          matrix.CalcComplements();
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

TEST(complement, not_square) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(
      {
        try {
          matrix.CalcComplements();
        } catch (const ComplementErr& e) {
          EXPECT_EQ(
              e.what(),
              "Algebraic addition: the matrix is not square or its size < 2x2");
          throw;
        }
      },
      ComplementErr);
}

TEST(complement, too_small) {
  S21Matrix matrix(1, 1);
  EXPECT_THROW(
      {
        try {
          matrix.CalcComplements();
        } catch (const ComplementErr& e) {
          EXPECT_EQ(
              e.what(),
              "Algebraic addition: the matrix is not square or its size < 2x2");
          throw;
        }
      },
      ComplementErr);
}

// Тест для корректной матрицы 2x2
TEST(complement, 2x2) {
  S21Matrix matrix(2, 2), expected(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  expected(0, 0) = 4;
  expected(0, 1) = -3;
  expected(1, 0) = -2;
  expected(1, 1) = 1;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

// Тест для корректной матрицы 3x3
TEST(complement, 3x3) {
  S21Matrix matrix(3, 3), expected(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

// Тест для матрицы, содержащей нули
TEST(complement, zero) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0;
  matrix(0, 1) = 0;
  matrix(0, 2) = 0;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;
  matrix(1, 2) = 0;
  matrix(2, 0) = 0;
  matrix(2, 1) = 0;
  matrix(2, 2) = 0;

  S21Matrix expected(matrix);
  expected(1, 1) = 0;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

/******************************************************************/

// Тест для пустой матрицы
TEST(inverse_test, empty) {
  S21Matrix matrix;
  EXPECT_THROW(
      {
        try {
          matrix.InverseMatrix();
        } catch (const VoidErr& e) {
          EXPECT_EQ(e.what(), "Used matrix is NULL");
          throw;
        }
      },
      VoidErr);
}

// Тест для неквадратной матрицы 2x3
TEST(inverse_test, not_square) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(
      {
        try {
          matrix.InverseMatrix();
        } catch (const InverseErr& e) {
          EXPECT_EQ(e.what(), "Inverse matrix: the matrix is not square");
          throw;
        }
      },
      InverseErr);
}

// Тест для слишком маленькой матрицы 1x1
TEST(inverse_test, too_small) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 1;
  EXPECT_THROW(
      {
        try {
          matrix.InverseMatrix();
        } catch (const InverseErr& e) {
          EXPECT_EQ(e.what(), "Inverse matrix: size of matrix is < 2x2");
          throw;
        }
      },
      InverseErr);
}

// Тест для матрицы 2x2 с нулевым определителем
TEST(inverse_test, singular_2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;
  EXPECT_THROW(
      {
        try {
          matrix.InverseMatrix();
        } catch (const InverseErr& e) {
          EXPECT_EQ(e.what(), "Inverse matrix: determinant of matrix is 0");
          throw;
        }
      },
      InverseErr);
}

// Тест для корректной матрицы 2x2
TEST(inverse_test, 2x2) {
  S21Matrix matrix(2, 2), expected(2, 2);
  matrix(0, 0) = 4;
  matrix(0, 1) = 7;
  matrix(1, 0) = 2;
  matrix(1, 1) = 6;

  expected(0, 0) = 0.6;
  expected(0, 1) = -0.7;
  expected(1, 0) = -0.2;
  expected(1, 1) = 0.4;

  S21Matrix result = matrix.InverseMatrix();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

// Тест для матрицы 3x3 с нулевым определителем
TEST(inverse_test, singular_3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  EXPECT_THROW(
      {
        try {
          matrix.InverseMatrix();
        } catch (const InverseErr& e) {
          EXPECT_EQ(e.what(), "Inverse matrix: determinant of matrix is 0");
          throw;
        }
      },
      InverseErr);
}

// Тест для корректной матрицы 3x3
TEST(inverse_test, 3x3) {
  S21Matrix matrix(3, 3), expected(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = 6;
  matrix(2, 2) = 0;

  expected(0, 0) = -24;
  expected(0, 1) = 18;
  expected(0, 2) = 5;
  expected(1, 0) = 20;
  expected(1, 1) = -15;
  expected(1, 2) = -4;
  expected(2, 0) = -5;
  expected(2, 1) = 4;
  expected(2, 2) = 1;

  S21Matrix result = matrix.InverseMatrix();
  EXPECT_EQ(result.EqMatrix(expected), true);
}
GCC = g++ -Wall -Werror -Wextra -std=c++17
LIBS = -lgtest -lpthread -lm
SRC = functions/*.cc
TEST_SRC= tests/main.cc

all: clean s21_matrix_oop.a check valgrind gcov_report

s21_matrix_oop.a:
	${GCC} -c ${SRC}
	ar rcs libs21_matrix_oop.a *.o
	rm *.o
	ranlib libs21_matrix_oop.a

test: clean s21_matrix_oop.a
	${GCC} ${TEST_SRC} -o test -L. -ls21_matrix_oop ${LIBS}
	./test

valgrind: clean s21_matrix_oop.a
	${GCC} ${TEST_SRC} -o test -L. -ls21_matrix_oop ${LIBS}
	valgrind --tool=memcheck --leak-check=yes ./test

gcov_report: clean s21_matrix_oop.a
	${GCC} --coverage ${TEST_SRC} -o test functions/* ${LIBS}
	./test
	lcov --capture --directory . -o coverage.info
	lcov --extract coverage.info '*/functions/*' -o coverage_filter.info
	genhtml --output-directory report --legend coverage_filter.info
	open report/index.html

clean:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info ./report ./test

check:
	clang-format -n functions/* tests/*
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ functions/* tests/*

correct:
	clang-format -i functions/* tests/* *.h

# docker run --name test -v /Users/tonikris/Documents/CPP1_s21_matrixplus-1/src/functions/:/functions -v /Users/tonikris/Documents/CPP1_s21_matrixplus-1/src/tests:/tests ubuntu
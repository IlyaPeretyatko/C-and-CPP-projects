UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	TEST_FLAGS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
endif
ifeq ($(UNAME),Darwin)
	TEST_FLAGS = $(shell pkg-config --cflags --libs check)
endif

CFLAGS = -Wall -Wextra -Werror -std=c11 -c


all: clean s21_matrix.a test gcov_report

test: test.o s21_matrix.a
	$(CC) test.o s21_matrix.a -o test -L. $(TEST_FLAGS)
	rm test.o
	./test

test.o:
	gcc $(CFLAGS) test.c -o test.o

s21_matrix.a: s21_matrix.o 
	ar rcs s21_matrix.a s21_matrix.o 
	ranlib s21_matrix.a
	rm s21_matrix.o

s21_matrix.o: s21_matrix.c
	gcc $(CFLAGS) s21_matrix.c -o s21_matrix.o


clean:
	rm -rf *.o *.a *.out *.info *.html *.gc* test gcov_report s21_matrix report

gcov_report:
	gcc -fprofile-arcs -ftest-coverage test.c s21_matrix.c -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

clang:
	clang-format -n -style=google *.c *.h

clang_update:
	clang-format -i -style=google *.c *.h

leak:
ifeq ($(UNAME),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind --leak-check=full -s --track-origins=yes ./test
endif

rebuild: all

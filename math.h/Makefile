UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	TEST_FLAGS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
endif
ifeq ($(UNAME),Darwin)
	TEST_FLAGS = $(shell pkg-config --cflags --libs check)
endif

CFLAGS = -Wall -Wextra -Werror -std=c11 -c
OS := $(shell uname)


all: clean s21_math.a test gcov_report

test: test.o s21_math.a
	$(CC) test.o s21_math.a -o test -L. $(TEST_FLAGS)
	rm test.o
	./test

test.o:
	gcc $(CFLAGS) test.c -o test.o

s21_math.a: s21_math.o
	ar rcs s21_math.a s21_math.o
	ranlib s21_math.a
	rm s21_math.o

s21_math.o: s21_math.c
	gcc $(CFLAGS) s21_math.c -o s21_math.o

clean:
	rm -rf *.o *.a *.out *.info *.html *.gc* test gcov_report s21_math report

gcov_report:
	gcc -fprofile-arcs -ftest-coverage test.c s21_math.c -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

clang:
	clang-format -n -style=google *.c *.h

clang_update:
	clang-format -i -style=google *.c *.h

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind --leak-check=full -s --track-origins=yes ./test
endif

rebuild: all

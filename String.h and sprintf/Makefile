UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	TEST_FLAGS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
endif
ifeq ($(UNAME),Darwin)
	TEST_FLAGS = $(shell pkg-config --cflags --libs check)
endif

CFLAGS = -Wall -Wextra -Werror -std=c11 -c


all: clean s21_string.a test gcov_report

test: test.o s21_string.a
	$(CC) test.o s21_string.a -o test -L. $(TEST_FLAGS)
	rm test.o
	./test

test.o:
	gcc $(CFLAGS) test.c -o test.o

s21_string.a: s21_string.o s21_sprintf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a
	rm s21_string.o

s21_string.o: s21_string.c
	gcc $(CFLAGS) s21_string.c -o s21_string.o

s21_sprintf.o: s21_sprintf.c
	gcc $(CFLAGS) s21_sprintf.c -o s21_sprintf.o

clean:
	rm -rf *.o *.a *.out *.info *.html *.gc* test gcov_report s21_string report

gcov_report:
	gcc -fprofile-arcs -ftest-coverage test.c s21_string.c s21_sprintf.c -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
ifeq ($(UNAME), Linux)
	xdg-open out/index.html
else
	open -a "Google Chrome" out/index.html
endif

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

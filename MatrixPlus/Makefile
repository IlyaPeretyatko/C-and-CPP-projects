FLAGS_TEST = -coverage -lgtest -lgtest_main -pthread
SOURCES = $(wildcard s21_*.cc)
OS = $(shell uname -s)
CFLAGS = -Wall -Wextra -Werror -c -std=c++17

all: clean s21_matrix_oop.a test

test: clean s21_matrix_oop.a
	g++ $(SOURCES) test.cc $(FLAGS_TEST) -o test
	./test

s21_matrix_oop.a:
	g++ $(CFLAGS) s21_matrix_oop.cc -o s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o 
	ranlib s21_matrix_oop.a
	rm s21_matrix_oop.o

clean:
	rm -rf *.o *.a *.gc* test s21_matrix_oop.a

clang:
	clang-format -n -style=google *.cc *.h

clang_update:
	clang-format -i -style=google *.cc *.h

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind --leak-check=full -s --track-origins=yes ./test
endif

rebuild: all

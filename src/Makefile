SYSSHELL:=$(shell uname)
CC=g++
CFLAGS=-Wall -Wextra -Werror -g
ifeq ($(SYSSHELL), Linux)
TFLAGS=-lgtest_main  -lgtest -lpthread --coverage 
else
TFLAGS=$(shell pkg-config --cflags --libs check) --coverage
endif



all: test

s21_matrix_oop.a:
	$(CC) $(CFLAGS) constructors.cpp functions.cpp get_set.cpp operators.cpp -c
	ar rvs s21_matrix_oop.a *.o
	rm -rf *.o

test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) test.cpp $(TFLAGS) -c
	$(CC) $(CFLAGS) test.o $(TFLAGS) -o test s21_matrix_oop.a

clean:
	rm -rf *.gcno *.info *.gcda *.o *.a test report

valgrind_check: test 
	valgrind -s  --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

.PHONY: s21_matrix_oop.a 
CC = g++ -std=c++20

FUNC = $(wildcard *.c)
OBJ = $(FUNC:.c=.o)

.PHONY: clean test my_matrix_oop.a leaks clang

all: my_matrix_oop.a

my_matrix_oop.a: $(OBJ)
	ar rcs $@ $^

%.o: %.c 
	$(CC) $< -o $@

test: my_matrix_oop.a
	$(CC) tests/test_matrix.cpp -o test -lgtest -lgmock -pthread
	./test

leaks:
	valgrind --tool=memcheck --leak-check=yes  ./test

clang:
	clang-format -i -style=google *.cpp *.h tests/*.cpp

clean:
	rm -f test *.a
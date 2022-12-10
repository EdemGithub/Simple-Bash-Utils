CC = gcc
FLAGS = -std=c11 -g -Wall -Wextra -Werror
ASAN = #-fsanitize=address

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) $(ASAN) s21_grep.c -o s21_grep

test:
	chmod +x test.sh
	./test.sh

clean:
	rm -r s21_grep
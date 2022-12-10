CC = gcc
FLAGS = -std=c11 -g -Wall -Wextra -Werror
ASAN = #-fsanitize=address

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) $(ASAN) s21_cat.c -o s21_cat

test:
	chmod +x cat.sh
	./cat.sh

clean:
	rm -r s21_cat
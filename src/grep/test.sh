#!/bin/bash

./s21_grep e s21_grep.c > s21_grep.txt
grep e s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -e "for" s21_grep.c > s21_grep.txt
grep -e "for" s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -i e s21_grep.c > s21_grep.txt
grep -i e s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -e 'A' 11 -e '[0-9]' > s21_grep.txt
grep -e 'A' 11 -e '[0-9]' > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -l e s21_grep.c s21_grep.c s21_grep.c > s21_grep.txt
grep -l e s21_grep.c s21_grep.c s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -c e s21_grep.c > s21_grep.txt
grep -c e s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -n e s21_grep.c > s21_grep.txt
grep -n e s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

./s21_grep -v e s21_grep.c > s21_grep.txt
grep -v e s21_grep.c > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt


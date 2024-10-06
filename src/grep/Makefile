CC=gcc -Wall -Werror -Wextra -std=c11

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o ./s21_grep

s21_grep.o: s21_grep.c
	$(CC) -c s21_grep.c

clean:
	rm -rf ./s21_grep *.o
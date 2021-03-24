CC=gcc
CFLAGS=-g -Wall -Werror -W -Wextra -pedantic -fsanitize=address #-Wwrite-strings
OBJ=src/main.o src/parse.o src/builtins.o src/minish.o src/redirect.o
BIN=minish

all=$(BIN)

minish: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o minish

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: tests
tests:
	./test.sh

clean:
	$(RM) -r minish *.o *.dSYM

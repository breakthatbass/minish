CC=gcc
CFLAGS=-g -Wall -Werror -W -Wextra -pedantic -fsanitize=address
OBJ=src/main.o src/parse.o src/builtins.o src/minish.o
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
	$(RM) -r minish src/*.o src/*.dSYM

CC=gcc
CFLAGS=-g -Wall -Werror -W -Wextra -pedantic -fsanitize=address
OBJ=main.o parse.o
BIN=minish

all=$(BIN)

minish: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o minish

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r minish *.o *.dSYM
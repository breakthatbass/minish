CC=gcc
CFLAGS=-ggdb3 -Wall -Werror -W -Wextra -pedantic -fsanitize=address
DIST=dist
OBJ=obj
SRC=src
BIN=minish

# get all .c files from src directory
SOURCES := $(wildcard src/*.c)
# go through those .c files and change .c to .o from SOURCES
OBJECTS := $(patsubst src/%.c, obj/%.o, $(SOURCES))

all: $(DIST)/$(BIN)

$(DIST)/$(BIN): $(DIST) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -ldl

# compile .c files to .o files that have corresponding .h files
$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h obj
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

# for main.c since there is no main.h
$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

# make directories
$(OBJ):
	mkdir $@

$(DIST):
	mkdir $@

.PHONY: tests
tests:
	./test.sh

clean:
	rm -rf $(OBJ)
	rm -rf $(DIST)

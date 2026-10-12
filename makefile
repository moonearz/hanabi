CC = gcc
CFLAGS = -g
RM = rm -f
NAME = hanabi
SRCS = $(wildcard *.c)
.PHONY: check format

default: all

all: game

game: game.c defs.h
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) hanabi

check:
	prek run --all-files

format:
	clang-format -i *.c *.h
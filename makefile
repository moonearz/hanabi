CC = gcc
CFLAGS = -g
RM = rm -f
NAME = hanabi
SRCS = $(wildcard *.c)

default: all

all: game

game: game.c defs.h
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) hanabi
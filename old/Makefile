# Makefile for Simulator
objects = main.o
CC = gcc
CFLAGS = -ansi -g -Wall -pedantic -lncurses
LIBS   = "-lncurses "


main: walls.o main.o
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $@

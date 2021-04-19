# Makefile for Simulator
objects = main.o walls.o
CC = gcc
CFLAGS = -ansi -g -Wall -pedantic -lncurses
LIBS   = "-lncurses "


main: main.o
	 $(CC) $(CFLAGS) $? $(LDFLAGS) -o $@

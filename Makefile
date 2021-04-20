
 #
 #  Microsim (µsim) - small life simulation game
 #  Copyright (C) 2021 Elias Leitinger (eliasleiti@gmail.com)
 #
 #  usim is free software: you can redistribute it and/or modify
 #  it under the terms of the GNU Affero General Public License as
 #  published by the Free Software Foundation, either version 3 of the
 #  License, or any later version.
 #
 #  usim is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU Affero General Public License for more details.
 #
 #  You should have received a copy of the GNU Affero General Public License
 #  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 #



# Makefile for Simulator
objects = main.o walls.o
CC = gcc
CFLAGS = -g -Wall -pedantic -lncurses
LIBS   = "-lncurses "


main: main.o
	 $(CC) $(CFLAGS) $? $(LDFLAGS) -o $@

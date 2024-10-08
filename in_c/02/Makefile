# Makefile shell for Mazes for Programmers

CC=clang
# CFLAGS=-Wall -O3 -std=c18
CFLAGS=-fsanitize=address -Wall -g3 -O0 -std=c18
# LDFLAGS=-lm
LDFLAGS=

SRCS=binary_tree.c binary_tree_demo.c cell.c grid.c sidewinder.c sidewinder_demo.c
HDRS=binary_tree.h cell.h grid.h sidewinder.h
OBJS=binary_tree.o binary_tree_demo.o cell.o grid.o sidewinder.o sidewinder_demo.o

.PHONY: clean all check-syntax reformat check-includes

check-syntax:
	$(CC) $(CFLAGS) -Wextra -Wpedantic -fsyntax-only $(SRCS)

reformat:
	astyle $(SRCS) $(HDRS)

check-includes:
	include-what-you-use *.c

clean:
	rm -rf *.o *.dSYM/

all: binary_tree_demo sidewinder_demo 

grid.o: grid.c grid.h cell.h
	$(CC) $(CFLAGS) -c grid.c

cell.o: cell.c cell.h
	$(CC) $(CFLAGS) -c cell.c

binary_tree.o: binary_tree.c grid.h cell.h binary_tree.h
	$(CC) $(CFLAGS) -c binary_tree.c

sidewinder.o: sidewinder.c grid.h cell.h sidewinder.h

binary_tree_demo: binary_tree_demo.o binary_tree.o cell.o grid.o
	$(CC) $(CFLAGS) -o binary_tree_demo binary_tree_demo.o binary_tree.o cell.o grid.o $(LDFLAGS)

sidewinder_demo: sidewinder_demo.o sidewinder.o cell.o grid.o
	$(CC) $(CFLAGS) -o sidewinder_demo sidewinder_demo.o sidewinder.o cell.o grid.o $(LDFLAGS)

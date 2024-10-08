# Makefile shell for Mazes for Programmers

CC=clang
# CFLAGS=-Wall -O3 -std=c18
CFLAGS=-fsanitize=address -Wall -g3 -O0 -std=c18
# LDFLAGS=-lm
LDFLAGS=

SRCS=
HDRS=
OBJS=

.PHONY: clean all check-syntax reformat check-includes

check-syntax:
	$(CC) $(CFLAGS) -Wextra -Wpedantic -fsyntax-only $(SRCS)

reformat:
	astyle $(SRCS) $(HDRS)

check-includes:
	include-what-you-use *.c

clean:
	rm -rf *.o *.dSYM/

all:

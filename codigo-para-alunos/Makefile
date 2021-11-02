SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default:	aplicacao

sort:	sort.c
		$(CC) $(CFLAGS) sort.c -o sort.o


aplicacao:	aplicacao.c sort.o
	$(CC) $(CFLAGS) aplicacao.c sort.o -o aplicacao

clean:
	rm -f aplicacao *.o core a.out *.*~ Makefile~

all: aplicacao

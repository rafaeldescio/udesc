SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default:	aplicacao

ABB.o:	ABB.c ABB_privado.h ABB.h
		$(CC) $(CFLAGS) -c ABB.c -o ABB.o

aplicacao:	aplicacao.c  aplicacao.h ABB.o
	$(CC) $(CFLAGS) aplicacao.c ABB.o -o aplicacao

clean:
	rm -f aplicacao *.o core a.out *.*~ Makefile~

all: aplicacao

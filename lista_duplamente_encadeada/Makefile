SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default: aplicacao

FEC.o:	LDDE.c LDDE.h LDDE_privado.h
	$(CC) $(CFLAGS) -c LDDE.c -o LDDE.o

aplicacao:	Aplicacao.c  Aplicacao.h pilha.o LDDE.o
	$(CC) $(CFLAGS) Aplicacao.c Aplicacao.h LDDE.o pilha.o -o aplicacao

clean:
	rm -f aplicacao  LDDE.o core a.out *.*~ Makefile~

all: aplicacao 

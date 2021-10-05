SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default: aplicacao

FEC.o:	FEC.c FEC.h FEC_privado.h
	$(CC) $(CFLAGS) -c FEC.c -o FEC.o

aplicacao:	Aplicacao.c  Aplicacao.h pilha.o FEC.o
	$(CC) $(CFLAGS) Aplicacao.c Aplicacao.h FEC.o pilha.o -o aplicacao

clean:
	rm -f aplicacao  FEC.o core a.out *.*~ Makefile~

all: aplicacao 

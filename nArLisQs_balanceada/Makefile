SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default:	aplicacao

libs/LDSE.o:	libs/LDSE.c libs/LDSE_privado.h libs/LDSE.h
			$(CC) $(CFLAGS) -ggdb3 -c libs/LDSE.c -o libs/LDSE.o

ArLisEx.o: ArLisEx.c ArLisEx.h ArLis_privado.h
		$(CC) -ggdb3 -c ArLisEx.c -o ArLisEx.o $(CFLAGS)

aplicacao:	aplicacao.c  aplicacao.h ArLis.o libs/LDSE.o ArLisEx.o libs/LDSEEx.o
	$(CC) $(CFLAGS) -ggdb3 aplicacao.c ArLisEx.o ArLis.o libs/LDSE.o libs/LDSEEx.o -o aplicacao

clean:
	rm -f aplicacao core a.out *.*~ Makefile~

all: aplicacao

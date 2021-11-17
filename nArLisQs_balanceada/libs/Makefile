SHELL=/bin/sh
CC=gcc
CFLAGS= -O3

default:	LDSEEx.o LDSE.o

LDSEEx.o:	LDSEEx.c LDSE_privado.h LDSEEx.h
		$(CC) $(CFLAGS) -c LDSEEx.c -o LDSEEx.o

clean:
	rm -f LDSEEx.o core a.out *.*~ Makefile~

all: aplicacao

CC=cc

LEX=/usr/bin/lex

COFLAGS=-O2
CWFLAGS=-Wall -Wextra

CFLAGS=$(COFLAGS) $(CWFLAGS)

all:		pretty

pretty.c:	pretty.l pretty.h
		$(LEX) -o pretty.c pretty.l

pretty.o:	pretty.c pretty.h
		$(CC) $(CFLAGS) -c pretty.c

error.o:	error.c pretty.h
		$(CC) $(CFLAGS) -c error.c

init.o:		init.c pretty.h
		$(CC) $(CFLAGS) -c init.c

symbol.o:	symbol.c pretty.h
		$(CC) $(CFLAGS) -c symbol.c

pretty:		pretty.o error.o init.o symbol.o pretty.h
		$(CC) $(CFLAGS) -o pretty pretty.o error.o init.o symbol.o

clean:	
		rm -f *.o pretty.c pretty

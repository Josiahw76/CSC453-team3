CC=cc
CPP=c++
LIBS=
COFLAGS=-g -O2
CWFLAGS=-Wall -Wextra
CIFLAGS=
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)
all:		lextest calcclass Calc compile
calcclass:	javaclass.h bytecode.h calcclass.c javaclass.o bytecode.o
		$(CC) $(CFLAGS) -o calcclass calcclass.c javaclass.o bytecode.o
Calc:		calcclass
		./calcclass
lextest:	lextest.o lexer.o error.o symbol.o init.o
		$(CC) $(CFLAGS) -o lextest lextest.o lexer.o error.o symbol.o init.o

lextest.o:	global.h lextest.c
		$(CC) $(CFLAGS) -c lextest.c

compile.o:	global.h compile.c
		$(CC) $(CFLAGS) -c compile.c

lexer.o:	global.h lexer.c
		$(CC) $(CFLAGS) -c lexer.c

error.o:	global.h error.c
		$(CC) $(CFLAGS) -c error.c

symbol.o:	global.h symbol.c
		$(CC) $(CFLAGS) -c symbol.c

init.o:		global.h init.c
		$(CC) $(CFLAGS) -c init.c


compile:	lexer.o error.o symbol.o init.o compile.o bytecode.o javaclass.o
		$(CC) $(CFLAGS) -o compile lexer.o error.o symbol.o init.o compile.o bytecode.o javaclass.o

clean:
		-rm -f lextest calcclass compile *.o *.class

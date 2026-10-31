CC=cc
YACC=yacc
LEX=lex
COFLAGS=-g -O2
CWFLAGS=-Wall -Wextra
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)

all:		mycc

mycc:		mycc.c bytecode.o error.o init.o javaclass.o symbol.o
		$(CC) $(CFLAGS) -o mycc mycc.c bytecode.o error.o init.o javaclass.o lex.yy.c symbol.o $(LIBS)

mycc.c:		mycc.l mycc.y
		$(LEX) --header-file=lex.yy.h mycc.l
		$(YACC) -o mycc.c -d -v mycc.y

bytecode.o:	bytecode.c javaclass.h bytecode.h
		$(CC) $(CFLAGS) -c $<

error.o:	error.c global.h
		$(CC) $(CFLAGS) -c $<

init.o:		init.c global.h mycc.h mycc.c
		$(CC) $(CFLAGS) -c $<

javaclass.o:	javaclass.c javaclass.h
		$(CC) $(CFLAGS) -c $<

symbol.o:	symbol.c global.h
		$(CC) $(CFLAGS) -c $<

.c.o:
		$(CC) $(CFLAGS) -c $<


.PHONY:		clean distclean
clean:
		-rm -f *.o mycc.c lex.yy.c mycc.h
distclean:
		-rm -f mycc *.o mycc.h mycc.c lex.yy.h lex.yy.c mycc.output Code.class

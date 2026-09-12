#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'


#define LEFT_CURLY       '{'
#define RIGHT_CURLY       '}'

// Josiah
#define LEFT_PAREN	'('
#define RIGHT_PAREN	')'
// I don't think the right paren is necessary, but the left is expected

#define DONE	300
#define ID	DONE+1

#define INT8	ID+1
#define INT16	INT8+1
#define INT32	INT16+1

#define IF	INT32+1
#define ELSE	IF+1

// Josiah
#define WHILE	ELSE+1
#define RET	WHILE+1
#define EQ	RET+1
#define PLUS	EQ+1
#define MINUS	PLUS+1
#define MULT	MINUS+1
#define DIV	MULT+1
#define MOD	DIV+1


// left_paren, while, return, =, +, -, *, /, %. 


extern void error(char *m);
extern void init();
extern int lexan();
extern int lookup(char s[]);
extern int insert(char s[], int tok, int var_index);
extern int assign_var_index(int tokenval);
extern int assign_var_index_ifZero(int index);
extern void dumpSumbolTable();

extern int varIndex;
extern int tokenval;
extern int lineno;

struct entry {
    char *lexptr;
    int token;
    // index into java frame vars for this variable, or -1 for keyword, or 0 for undeclared symbol
    int var_index;

};

extern struct entry symtable[];

#endif

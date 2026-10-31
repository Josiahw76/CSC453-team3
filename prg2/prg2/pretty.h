#ifndef P2_H
#define P2_H

#define LT_CBRACE       '{'
#define RT_CBRACE       '}'
#define LT_PAREN        '('
#define RT_PAREN        ')'
#define LT_SQBRACE      '['
#define RT_SQBRACE      ']'
#define ASSIGN  '='
#define ADD    '+'
#define SUB   '-'
#define MUL     '*'
#define DIV     '/'
#define MOD     '%'
#define NOT	'!'
#define BAND	'&'
#define BOR 	'|'
#define BNOT 	'^'

#define DONE	300
#define ID	(DONE+1)
#define NUM	(ID+1)
#define IF	(NUM+1)
#define ELSE	(IF+1)
#define FOR	(ELSE+1)
#define WHILE	(FOR+1)
#define DO	(WHILE+1)
#define BREAK	(DO+1)
#define CONTINUE	(BREAK+1)
#define SWITCH	(CONTINUE+1)
#define CASE	(SWITCH+1)
#define RETURN	(CASE+1)

#define RELOP	(RETURN+1)
#define LT	(RELOP+1)
#define GT	(LT+1)
#define LEQ	(GT+1)
#define GEQ	(LEQ+1)
#define EQUIV	(GEQ+1)
#define NOTEQUIV	(EQUIV+1)

#define OPERATOR (NOTEQUIV+1)
#define BOOLOP   (OPERATOR+1)
#define LAND     (BOOLOP+1)
#define LOR      (LAND+1)
#define BINOP	 (LOR+1)
#define BOOLOP1  (BINOP+1)
#define DEREF	 (BOOLOP1+1)

#define DEFAULT		(DEREF+1)
#define CHAR		(DEFAULT+1)
#define SHORT		(CHAR+1)
#define INT		(SHORT+1)
#define LONG		(INT+1)
#define FLOAT		(LONG+1)
#define DOUBLE		(FLOAT+1)
#define UNSIGNED	(DOUBLE+1)
#define VOID		(UNSIGNED+1)
#define STATIC		(VOID+1)
#define VOLATILE	(STATIC+1)
#define EXTERN		(VOLATILE+1)
#define STRUCT		(EXTERN+1)
#define TYPEDEF		(STRUCT+1)
#define SIZEOF		(TYPEDEF+1)


#define SYMMAX	1024

extern int yylval;
extern int yylex();
extern char *yytext;
extern int installID(char *str, int tk, int var_index);
extern int installNUM(char *str, int tk, int num_index);
extern int lookupVar_index(char s[]);
extern void dumpSymbolTable();

struct entry {
    char *lexptr;
    int token;
    // index into java frame vars for this variable, or -1 for keyword, or 0 for undeclared symbol
    int var_index;

};
extern int lastentry;
extern int symEntry;

extern struct entry symtable[];

extern void error(char *s);
extern void myInit();

#endif

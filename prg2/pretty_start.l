%{
# TO BE NAMED p2.l

#include <stdio.h>
#include "pretty.h"

#define TRUE (1)
#define FALSE (0)

#define INDENT (4)

int line = 0;
int column = 4;
int paren = 0;
int inComment = 0;
int debug = 1;

void write_indent();
void write_html();
void write_html_char(int);
void write_string();
void write_char();
void write_oct();
void write_hex();
void write_int();
void write_fp();
void write_id();
void write_begin();
void write_end();
void write_open();
void write_close();
void write_bopen();
void write_bclose();
void write_sep();
void write_op();
void write_inline();
void write_comment();
void write_directive();

%}

%option	noyywrap
%option	yylineno

quote	\'
ditto	\"
delim	
ws	
alpha
digit
oct	
exp	
hex	
id	
number	

%%


{ws}				{ /* no action and no return */ }
{quote}([^']|\\')*{quote}	write_char();
{ditto}([^"]|\\\")*{ditto}	write_string();
something			write_oct();
something			write_hex();
something			write_int();
something	                write_fp();
something	                write_id();
left curly			write_begin();
something			write_end();
left_paren			write_open();
something			write_close();
"["				write_bopen();
"]"				write_bclose();
";"				write_sep();
"+"				|
"+="				|
many more such lines            |
"::"				write_op();
inline comment			write_inline();
/* */ style comment     	write_comment();
#define type command    	write_directive();
.				printf("unrecognized input at line %d", yylineno);

%%


int main() {
    myInit();
    printf("<html><pre>\n");
    yylex();
    printf("\n</pre></html>\n");
    return 0;
}

void write_indent() {
    printf("\n%-*d", column, line++);
}

void write_html_char(int c) {
    switch (c) {
	case '<':
	    printf("&lt;");
	    break;
	case '>':
	    printf("&gt;");
	    break;
	case '"':
	    something;
	    break;
	case '&':
	    something;
	    break;
	case '\n':
	    if (inComment) {
		printf("\n%-*d", column, line++);
	    }
	    break;
	default:
	    putchar(c);
    }
}

void write_html() {
    char *s = yytext;

    while (*s) {
	write_html_char(*s++);
    }
}

void write_char() {
    if (debug) {
	fprintf(stderr, "write_char: %s\n", yytext);
    }
    printf("<u><font color='brown'>");
    write_html();
    printf("</font></u> ");
}

void write_string() {
    something;
}

void write_oct() {
    something;
}

void write_hex() {
    something;
}

void write_int() {
    something;
}

void write_fp() {
    something;
}

void write_id() {
    int kw = FALSE;
    int id = lookupVar_index(yytext);

    if (id == -2) {
	// this is the first time we've seen this ID
	installID(yytext, ID, line);
	printf("<a name='%s'>", yytext);
    } else if (id >= 0) {
	printf("<a href='#%s'>", yytext);
    } else {
    	// it's a keyword
	printf("<b>");
	kw = TRUE;
    }
    if (debug) {
	fprintf(stderr, "write_id: %s; kw = %d\n", yytext, kw);
    }

    printf("<font color='blue'>");
    write_html();
    printf("</font>");

    if (kw)  {
	printf("</b> ");
    } else {
	printf("</a>");
    }
}

void
write_begin() {
    putchar(' ');
    write_html();
    write_indent();
    column += INDENT;
    write_indent();
}

void
write_end() {
    something;
}

void
write_open() {
    write_html();
    paren++;
}

void
write_close() {
    something;
}

void
write_bopen() {
    write_html();
    paren++;
}

void
write_bclose() {
    something;
}

void
write_sep() {
    if (debug) {
	fprintf(stderr, "write_sep: %s\n", yytext);
    }
    write_html();
    if (!paren) {
	write_indent();
    } else  {
	putchar(' ');
    }
}

void
write_op() {
    if (debug) {
	fprintf(stderr, "write_op: %s\n", yytext);
    }
    putchar(' ');
    printf("<b>");
    write_html();
    printf("</b> ");
    putchar(' ');
}

void
write_inline() {
    something;
}

void
write_comment() {
    if (debug) {
	fprintf(stderr, "write_comment: %s\n", yytext);
    }
    inComment = TRUE;
    printf("<font color='green'>");
    write_html();
    printf("</font>");
    write_indent();
    inComment = FALSE;
}

void
write_directive() {
    something;
}

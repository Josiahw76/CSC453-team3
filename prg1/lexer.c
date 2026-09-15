// Name: 
// Assignment: Program 1 - Part 1
// Class: CSC453 Fall 2022
// File: lexer.c

#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

int lexan() {
    int t;
    int rc;

	// Josiah - I'm gonna leave comments in here for myself to understand

    while (1) {
	t = getchar();

	if (t== ' ' || t == '\t') {
	}
	else if (t == '\n') {
	    lineno = lineno + 1;
		// prior if and if else process whitespace and newlines
	} else if (isdigit(t)) {
		// digit handling from here to break statement
	    ungetc(t, stdin); // digit; put it back on the input stream.
	    scanf("%d", &tokenval); // read as an integer with %d, put to tokenval
	    if (tokenval < 256) { // now process tokenval
		rc = INT8;
	    } else if (tokenval < 65536) {
		rc = INT16;
	    } else {
		rc = INT32;
	    }
	    break;
	} else if (isalpha(t) || t == '_') {
		// we've discovered a non-terminal, start to process it
	    int p, b = 0;

	    while (isalnum(t) || t == '_') {
		// collect the characters and assemble into a string
			lexbuf[b] = t;
			t = getchar();
			b = b + 1;

			if (b >= BSIZE) { // panic and terminate the program entirely
		    	error("compiler error");
			}
	    }

	    lexbuf[b] = EOS; // just a null terminator '\0'
			     // now it's a proper string literal

		// tie up loose end from looping behavior
	    if (t != EOF) {
		ungetc(t, stdin);
	    }

		
	    p = lookup(lexbuf); // this line is how we get our MULT, WHILE,
				// all those symbols out of the table

	    if (p == -1) { // does it exist in our table yet?
		//printf("** calling insert\n");
		p = insert(lexbuf, ID, varIndex);
		varIndex++;
	    }

	    tokenval = p;

	    rc = symtable[p].token;

	    break;
	} else if (t == EOF) {
	    rc = DONE;
	    break;
	} else {
	    tokenval = NONE;
	    rc = t;
	    break;
	}
    }

    return(rc);
}

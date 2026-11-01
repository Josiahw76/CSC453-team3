/* TODO: TO BE COMPLETED */

#include "global.h"

/* TODO: define a symbol table/array, reuse project Pr1 */

// Adapted from prg1 by Josiah

#define SYMMAX 100

struct symbol symtable[SYMMAX];
int lastentry 0;

Symbol *lookup(const char *s)
{
    int p;
    Symbol *rc;

    for (p = 0; p < lastentry; p++) {
	if (strcmp(symtable[p].lexptr, s) == 0) {
	    // Return a symbol pointer instead of integer
	    rc = &symtable[p];
	    break;
	}
    }
    return(rc);
}

Symbol *insert(const char *s, int token) 
{
    if (lastentry+1 == SYMMAX) {
	error("symbol table full");
    }

    symtable[lastentry].token = tok;

    symtable[lastentry].lexptr = (char *)malloc(strlen(s)+1);
    strcpy(symtable[lastentry].lexptr, s);

    // symtable[lastentry].var_index = javaIndex;
    // artifact from prog1

    lastentry++;

    // Adapted to return a pointer instead of the index
    return(&symtable[lastentry-1]);
}

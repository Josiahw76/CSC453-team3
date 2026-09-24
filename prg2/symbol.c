#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretty.h"

struct entry symtable[SYMMAX];

int lastentry = 0;
int symEntry = 0;

int lookupID(char s[]) {
    int p;
    int rc = -1;

    for (p = 0; p < lastentry; p++) {
	if (strcmp(symtable[p].lexptr, s) == 0) {
	    rc = p;
	    break;
	}
    }
    return(rc);
}

int lookupVar_index(char s[]) {
    int p;
    int rc = -2;

    for (p = 0; p < lastentry; p++) {
	if (strcmp(symtable[p].lexptr, s) == 0) {
	    rc = symtable[p].var_index;
	    break;
	}
    }
    return(rc);
}

int installID(char s[], int tk, int var_index) {
    int rc;

    rc = lookupID(s);

    if (rc == -1) {
	// the identifier does not exist yet
	if (lastentry+1 == SYMMAX) {
	    error("symbol table full");
	}

	symtable[lastentry].token = tk;

	symtable[lastentry].lexptr = (char *)malloc(strlen(s)+1);
	strcpy(symtable[lastentry].lexptr, s);

	if (var_index == 0) {
	    symtable[lastentry].var_index = symEntry++;
	} else {
	    symtable[lastentry].var_index = var_index;
	}

	rc = lastentry;
	lastentry++;
    }


    return(rc);
}

int installNUM(char s[], int tk, int num_index) {
    return(1);
}

void dumpSymbolTable() {
    int i;
    fprintf(stderr, "Symbol table as %d entries\n", lastentry);

    for (i = 0; i < lastentry; i++) {
	fprintf(stderr, "%3d: ", i);
	fprintf(stderr, "var_index = %3d for symbol %s\n", symtable[i].var_index, symtable[i].lexptr);
    }
}

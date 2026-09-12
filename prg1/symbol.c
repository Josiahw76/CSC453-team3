// Name: 
// Assignment: Program 1 - Part 1
// Class: CSC453 Fall 2026
// File: symbol.c

#include "global.h"

#define STRMAX 999
#define SYMMAX 100

char lexemes[STRMAX];

int lastchar = -1;

struct entry symtable[SYMMAX];

int lastentry = 0;
int varIndex = 3;       /* UPDATE WHEN NECESSARY */

int lookup(char s[]) {
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

int insert(char s[], int tok, int javaIndex) {
    // javaIndex is the index of the java memory frame for the current method.
    // The first three (0..2) are taken already, so our entries must be given indexes at 3 and above.
    //
    // Since a symbol may be used more than once in the program, care must be taken to ensure
    // subsequent uses of that symbol do not get new javaIndex values.
    //
    // For that reason, I have introduced a new helper function below to assign javaIndex
    // to a symbol only if it doesn't have a javaIndex (var_index in the structure)
    // assigned to it already.
    //
    // NOTE!!!!!
    // There are two indexes at play; we have our index into our symbol table, which starts at 0.
    // Each of our unique ID's will get stored in our table at an index.
    // But each variable will still get a Java storage javaIndex (var_index), starting at 3.

    if (lastentry+1 == SYMMAX) {
	error("symbol table full");
    }

    symtable[lastentry].token = tok;

    symtable[lastentry].lexptr = (char *)malloc(strlen(s)+1);
    strcpy(symtable[lastentry].lexptr, s);

    symtable[lastentry].var_index = javaIndex;

    lastentry++;


    return(lastentry-1);
}

int assign_var_index(int index) {
    symtable[index].var_index = varIndex;
    varIndex++;

    return symtable[index].var_index;
}

int assign_var_index_ifZero(int index) {
    if (symtable[index].var_index == 0) {
	symtable[index].var_index = varIndex;
	varIndex++;
    }

    return symtable[index].var_index;
}

void dumpSumbolTable() {
    int i;
    fprintf(stderr, "Symbol table as %d entries\n", lastentry);

    for (i = 0; i < lastentry; i++) {
	fprintf(stderr, "%3d: ", i);
	fprintf(stderr, "javeLoc = %3d for symbol %s\n", symtable[i].var_index, symtable[i].lexptr);
    }
}

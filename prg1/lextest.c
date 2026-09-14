// Name: 
// Assignment: Program 1 - Part 1
// Class: CSC453 Fall 2022
// File: lextest.c

#include <stdio.h>
#include "global.h"

int
main(int argc, char* argv[])
{
    init();

    fprintf(stderr, "argc = %d\nargv[0] = %s\n", argc, argv[0]);

    int t = 0;
    do {
	t=lexan();
	if (t != NONE) {
	    putchar('<');
	    if (t < DONE) {
		printf("%c,%d> ", (char)t, -1);
	    } else {
		switch(t) {
		    case DONE:
			printf("DONE");
			printf(",%d> ", symtable[tokenval].var_index);
			break;
		    case ID:
			// WIP
			printf("ID");
			printf(",%d> ", symtable[tokenval].var_index);
			break;
		    case ARG:
			printf("ARG");
			printf(",%d> ", symtable[tokenval].var_index);

			break;
		    case INT8:
			printf("INT8");
			printf(",%d> ", tokenval);
			break;
		    case INT16:
			printf("INT16");
			printf(",%d> ", tokenval);
			break;
		    case INT32:
			printf("INT32");
			printf(",%d> ", tokenval);
			break;

		}
	    }
	}
    } while (!(t == DONE || t == EOF));
    putchar('\n');
    return 0;
}

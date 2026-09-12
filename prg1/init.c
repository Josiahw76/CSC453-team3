// Name: 
// Assignment: Program 1 - Part 1
// Class: CSC453 Fall 2026
// File: init.c

#include "global.h"

struct entry keywords[] =
{
    {"if", IF, -1}, // Associates the keyword if with the value of IF
		    // as defined in global. The entries to be completed
		    // must be defined in the same way here
		    //
		    // "keyword", KEYWORD, -1 for keyword
    // TO BE COMPLETED
    {0, 0, 0}
};

void init() {
    struct entry *p;

    for (p = keywords; p->token; p++) {
	insert(p->lexptr, p->token, p->var_index);
    }
}

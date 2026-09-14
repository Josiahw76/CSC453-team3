// Name: 
// Assignment: Program 1 - Part 1
// Class: CSC453 Fall 2026
// File: init.c

#include "global.h"

struct entry keywords[] =
{
    {"else", ELSE, -1},
    {"if", IF, -1},

    // Josiah
    {"while", WHILE, -1},
    {"return", RET, -1},
    {"arg", ARG, -1},
    {"=", EQ, -1},
    {"+", PLUS, -1},
    {"-", MINUS, -1},
    {"*", MULT, -1},
    {"/", DIV, -1},
    {"%", MOD, -1},

	// DONE is not included here because lexan() uses that when needed.
	// It is not a recognized keyword in our grammar	

    {0, 0, 0}
};

void init() {
    struct entry *p;

    for (p = keywords; p->token; p++) {
	insert(p->lexptr, p->token, p->var_index);
    }
}

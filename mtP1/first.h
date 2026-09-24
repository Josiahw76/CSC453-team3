#ifndef __FIRST_H
#define __FIRST_H

#include "global.h"
#include "symList.h"

struct grammar {
	production *P; // array of productions
	symList T; // terminals
	symList A; // non-terminals
	symbol S; // Start symbol. This will be included in P
};



// This is a top-level call.
// Perhaps it would be better for it to also perform reading?
extern void First(grammar &gram); // pass by reference
extern grammar First(); // maybe this is more ideal. simply returns a grammar
extern char lexan();
extern void printIt();

#endif

/*
grammar syntax/format example
S -> aBa | bCb ;
B -> a | b ;
C -> def | fed ;
C -> dog ;

some observations:
first character is start symbol
uppercase characters represent non-terminals
lowercase characters represent terminals

C's productions can be combined. This would mean expanding an array.
yet another reason to use lists: lookups.

 */

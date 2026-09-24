#ifndef __GLOBAL_H
#define __GLOBAL_H

#define EPSILON '&'


class grammar {
	public:	
		production *P; // array of productions
		symList *T; // terminals
		symList *A; // non-terminals
		symbol S; // Start symbol. This will be included in P
		
		inline void printIt() {

		}
		inline grammar() {
			
		}
		inline void expand_productions() {
			
		}
};

inline char lexan(FILE *file) {
	char c;
	do { c = fgetc(file) } while (c == ' '); // skip blanks
	return c;
}


struct symbol {
    bool isTerm; // tells us how to treat the symbol. false means it must
		     // derive to something.
		     // all symbols with a isTerm of false can be found
		     // in productions
    char name;  // alternatively could just be char, but can't
		     // guarantee grammar will be individual characters
};

struct production {
    symbol non_t; // left hand side
    symList *derivation; // Collection of symbols on rhs
};

#endif

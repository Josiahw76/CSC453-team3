#ifndef __GLOBAL_H
#define __GLOBAL_H

#define EPSILON '&'

struct symbol {
    bool isTerm; // tells us how to treat the symbol. false means it must
		     // derive to something.
		     // all symbols with a isTerm of false can be found
		     // in productions
    char *name;  // alternatively could just be char, but can't
		     // guarantee grammar will be individual characters
};

struct production {
    symbol non_t; // left hand side
    symbol *derivation; // Collection of symbols on rhs
};

#endif

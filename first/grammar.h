#ifndef __GRAMMAR_H
#define __GRAMMAR_H

#include "global.h"
#include "symList.h"
#include <stdio.h>

// Author: Josiah W

class grammar {
	private:
		production *P; // array of productions
		symbol S; // Start symbol. This will be included in P
		
		unsigned int productionCount;
		FILE *file;

		firstSet first(symbol sym); // The meat and taters
		

	public:	
		symList *T; // terminals
		symList *A; // non-terminals

		void setStart(symbol S);
		symbol getStart() const;

		bool addProduction(production *p); // done
		unsigned int getProdCount(); // done
		grammar(const char *filename); // done
		void printIt();
		bool productionExists(symbol sym); // done
		int findProduction(symbol non_t);
		production& getProduction(symbol non_t);
	 	int lexan(); // done

		firstSet *first(); // Helper function: gets first of all terminal 
			      // and non-terminal symbols in the grammar.
};

#endif

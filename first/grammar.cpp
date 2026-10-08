#include "grammar.h"
#include "global.h"
#include "symList.h"
#include <stdio.h>
#include <iostream>

// Author: Josiah W

using namespace std;

grammar::grammar(const char *filename) {
	P = new production[100];
	T = new symList(10);
	A = new symList(10);

	this->productionCount = 0;

	file = fopen(filename, "r");
}

int grammar::lexan() {
	int c;
	do {
		c = fgetc(file); 	
	} while (c == ' ' || c == '\n' || c == '\t'); // skip blanks & new lines and tabs because lexan read new lines
	return c;
}

bool grammar::productionExists(symbol sym) {
	bool rc = false;
	for (unsigned int i = 0; i < productionCount; i++) {
		if (sym.name == P[i].non_t.name) {
			rc = true;
			break;	
		}	
	}
	return rc;
}

production& grammar::getProduction(symbol non_t) {
	return P[findProduction(non_t)];

}

bool grammar::addProduction(production *p) {
	bool rc = productionCount < 100;
	// add to P[productionCount]
	if (rc) {
		P[productionCount] = *p;
		productionCount++;
	} else {
		printf("ahh its too feature rich\n");
	}
	return rc;
}

int grammar::findProduction(symbol non_t) {
	int rc = -1;
	for (unsigned int i = 0; i < productionCount; i++) {
		if (non_t.name == P[i].non_t.name) {
			rc = (int)i;
			break;
		}
	}
	return rc;
}


unsigned int grammar::getProdCount() {
	return productionCount;
}

void grammar::setStart(symbol S) {
	this->S = S;
}

symbol grammar::getStart() const{
	return S;
}

void grammar::printIt() {
    // in order: start symbol, non-terminals, terminals, productions
	// productions will imitate the grammar structure
	symbol sym;
	cout << "Start symbol: \t" << S.name << endl;
	cout << "Non-terminals:\t";
	unsigned int count = A->getCount();
	for (unsigned int i = 0; i < count; i++) {
		if (A->getSymbol(i, sym)) {
			cout << sym.name << ", ";
		}
	}
	cout << endl;
	cout << "Terminals:\t";
	count = T->getCount();
	for (unsigned int i = 0; i < count; i++) {
		if (T->getSymbol(i, sym)) {
			cout << sym.name << ", ";
		}
	}
	cout << "\n\n";
	cout << "Productions:\n";
	count = A->getCount();
	unsigned int rhs_counter;
	for (unsigned int i = 0; i < count; i++) {
		// Iterate for non-terminals
		// cout << "d_count = " << P[i].d_count << endl;
		cout << P[i].non_t.name << "  ->\t  ";
		

		for (unsigned int j = 0; j < P[i].d_count; j++) {
			// Iterate for right hand sides
			if (j > 0) {
				// add in the vertical line for second and on
				cout << "  \t| ";
			}
			rhs_counter = P[i].derivations[j]->getCount();
			for (unsigned int k = 0; k < rhs_counter; k++) {
				P[i].derivations[j]->getSymbol(k, sym);
				cout << sym.name;
			}
			cout << " ;\n";
		}
	}
}

/******************************************************************************/

// Author: Josiah

// This is where epsilon will need to be represented as &.
// Discovering a non-terminal in a production will result in recursive
// First calls until the list is fully resolved.
//
// To start, we iterate through our productions.

//***********************************
// We need a cat function for symList <- done
// **********************************

symList *grammar::first(symbol sym) {

	unsigned int rhs_count, rhs_length;
	symbol tempSym;	
	symList *tempList;
	symList *inFirst = new symList(10);

	// Copy the production out of the list for easier access.
	// Note that this is an object and not a pointer
	production firstOf = P[findProduction(sym)];

	
	if (!((sym.name == '&') || T->inList(sym))) {
		// If sym itself is a terminal or epsilon, go to else block.

		// First things first, iterate across our productions.
		rhs_count = P[findProduction(sym)].d_count;
		// Nested for loops are necessary as derivations
		// come in the form of a 2d array
		for (unsigned int i = 0; i < rhs_count; i++) {
			rhs_length = firstOf.derivations[i]->getCount();

			for (unsigned int j = 0; j < rhs_length; j++) {
				firstOf.derivations[i]->getSymbol(j, tempSym);
				if (tempSym.isTerm) {
					inFirst->addNew(tempSym);
					break;
				} else if (tempSym.name == '&') {
					inFirst->addNew(tempSym);

				} else { // Else it is a non-terminal
					// Add everything in first of
					// the symbol to our first.
					tempList = first(tempSym);
					inFirst->cat(tempList);
					delete tempList;
				}
			}
		}
	} else {
		// If the symbol itself is a terminal or epsilon, return
		// it by itself
		inFirst->add(sym);
	}
	// trim the list down. Why? I want to justify having written the code
	// for cut()
	inFirst->cut();
	return inFirst;
}

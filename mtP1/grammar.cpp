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
	} while (c == ' '); // skip blanks
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

production grammar::getProduction(symbol non_t) {
	return P[findProduction(non_t)];

}

bool grammar::addProduction(production p) {
	bool rc = productionCount < 100;
	// add to P[productionCount]
	if (rc) {
		P[productionCount] = p;
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

void grammar::printIt() {
    // in order: start symbol, non-terminals, terminals, productions
	// productions will imitate the grammar structure
	symbol sym;
	cout << "Start symbol: " << S.name << endl;
	cout << "Non-terminals:" << endl;
	unsigned int count = A->getCount();
	for (unsigned int i = 0; i < count; i++) {
		if (A->getSymbol(i, sym)) {
			cout << sym.name << endl;
		}
	}
	cout << "Terminals:\n";
	count = T->getCount();
	for (unsigned int i = 0; i < count; i++) {
		if (T->getSymbol(i, sym)) {
			cout << sym.name << endl;
		}
	}

}

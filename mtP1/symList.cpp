#include "global.h"
#include "symList.h"

symList::symList(unsigned int listCapacity) {
    this->listCapacity = listCapacity;
    symbols = new symbol[listCapacity];
    listCount = 0;
}

void symList::expand() {
    symbol *newl = new symbol[listCapacity + 1];
    for (unsigned int i = 0; i < listCount; i++) {
	    newl[i] = symbols[i];

    }
    delete [] symbols;
    symbols = newl;
}

void symList::add(symbol sym) {
    if (listCount == listCapacity) {
		expand();	
	}
	symbols[listCount] = sym;
	listCount++;
}

bool symList::inList(symbol sym) {
	bool rc = false;

	for (unsigned int i = 0; i < listCount; i++) {
		if (sym.name)

	return rc
}

void symList::addNew(symbol sym) {
	if (!inList(sym)) {
		add(sym);
	}
}

void symList::cut() {
	if (listCount < listCapacity) {
		symbol *newl = new symbol[listCount];
		for (unsigned int i = 0; i < listCount; i++) {
			newl[i] = symbols[i];
		}
		delete [] symbols;
		symbols = newl;
	}
}

symbol symList::getSymbol(char *target) {
	symbol sym = {.isTerm = 0}; // default is null term

	for (unsigned int i = 0; i < listCount; i++) {
		if (symbols[i].name == target) {
			sym = symbols[i];
		}
	}

	return sym;
}

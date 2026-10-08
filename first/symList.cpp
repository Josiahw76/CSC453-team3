#include "grammar.h"
#include "global.h"
#include "symList.h"
#include <stdio.h>
#include <iostream>

// Author: Josiah W

using namespace std;

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

bool symList::inList(symbol sym) const {
	bool rc = false;
	for (unsigned int i = 0; i < listCount; i++) {
		if (sym.name == symbols[i].name) {
		    rc = true;
		    break;
		}
	}
	return rc;
}

bool symList::getSymbol(unsigned int index, symbol &sym) const {
	bool rc = index < listCount;
	if (rc) {
		sym = symbols[index];
	}
	return rc;
}


symbol symList::getSymbol(char target) const {
	symbol sym = {.isTerm = 0, .name = ' '}; // default is null term

	for (unsigned int i = 0; i < listCount; i++) {
		if (symbols[i].name == target) {
			sym = symbols[i];
		}
	}

	return sym;
}
/*
symbol symList::getSymbol(unsigned int index) const {
	symbol sym = {.isTerm = 0, .name = ' '}; // default is null term

	if (index > 0 && index < listCount) {
		sym = symbols[index];
	}
	return sym;
}
*/
void symList::add(symbol sym) {
    if (listCount == listCapacity) {
		expand();	
	}
	symbols[listCount] = sym;
	listCount++;
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

unsigned int symList::getCount() const {
	return listCount;
}

unsigned int symList::getCapacity() const {
	return listCapacity;
}

void symList::cat(symList *list2) {
	// This should work just fine, hasn't really been tested.
	unsigned int i, j, list2count;
	symbol temp;
	list2count = list2->getCount();	
	symbol *catted = new symbol[listCount + list2count];

	for (i = 0; i < listCount; i++) {
		catted[i] = symbols[i]; 
	}
	for (j = 0; j < list2count; j++) {
		list2->getSymbol(j, temp);
		catted[i + j] = temp;
	}
	delete [] symbols;
	symbols = catted;
}

void symList::dumpList() const {
	cout << "\nSymbol list has " << listCount << " entries.\n";
	for (unsigned int i = 0; i < listCount; i++) {
		cout << symbols[i].name << ", ";
	}
}

#ifndef __SYMLIST_H
#define __SYMLIST_H

#include "global.h"
#include "grammar.h"

// Author: Josiah W

class symList {
	private:
		symbol *symbols;			
		unsigned int listCapacity;
		void expand();

	public:
		unsigned int listCount;

		symList(unsigned int listCapacity);
		symbol getSymbol(char target);
		bool getSymbol(unsigned int index, symbol &sym);
		bool inList(symbol sym);
		void addNew(symbol sym);
		void add(symbol sym);
		void cut();	
		unsigned int getCount();

};

#endif

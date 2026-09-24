#ifndef __SYMLIST_H
#define __SYMLIST_H

#include "global.h"

// definition for symbol

class symList {
	private:
		symbol *symbols;			
		unsigned int listCapacity;
		void expand();

	public:
		unsigned int listCount;

		symList(unsigned int listCapacity);
		symbol getSymbol(char *target);
		bool inList(symbol sym);
		void addNew(symbol sym);
		void add(symbol sym);
		void cut();	

};

#endif

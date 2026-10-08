#ifndef __SYMLIST_H
#define __SYMLIST_H

#include "global.h"
#include "grammar.h"

// Author: Josiah W

class symList {
	private:
		symbol *symbols;			
		unsigned int listCapacity;
		unsigned int listCount;		
		void expand();

	public:

		bool inList(symbol sym) const;
		symList(unsigned int listCapacity);
		bool getSymbol(unsigned int index, symbol &sym) const;		
		symbol getSymbol(char target) const;
		// symbol getSymbol(unsigned int index) const;
		void add(symbol sym);
		void addNew(symbol sym);
		void cut();	
		unsigned int getCount() const;
		unsigned int getCapacity() const;
		void cat(symList *list2);

		void dumpList() const;

};

#endif

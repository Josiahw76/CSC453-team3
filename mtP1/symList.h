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
		void add(symbol sym);
		void cut();	

};

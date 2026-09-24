#include "global.h"
#include "symList.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	// Phase 1: lexical analysis

	FILE *file = fopen("grammar.txt");
	char c;
	bool first = true;
	grammar *gram = new grammar();
	symbol token;

	while (true) {
		c = lexan(file);

		switch (c) {
				// [65-90] = [A-Z]
				case (c <= 90 || c >= 65):
					if (first) {
						token.name = c;
						token.isTerm = false;
						gram->S = symbol;
					}
				break;
				case ('-'):
					if (fgetc(file) != '>') {
						cerr("Expected '>' character");
						exit();
					}

					// Now we're reading a production
					do {	
						c = lexan();

						// is it lowercase? [97-122]
						if (c >= 97 && c <= 122) {
							// put it into the terminal list (chris pratt?)
							token.isTerm = true;
							token.name = c;
							gram->T->add(token);
							continue;
						} else if (c <= 90 || c >= 65) {
							token.isTerm = false;
							token.name = c;
							gram->A->add(token);


					} while (c != ';' && c != '|');
					
					

		}	
	}

	// S -> aBa | bCb ;
	// ^
	//   ^

	// Phase 2: storage into data structure

	// Phase 3: representation of grammar
	
	return 0;
}

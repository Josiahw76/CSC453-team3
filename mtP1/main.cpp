#include "grammar.h"
#include "global.h"
#include "symList.h"
#include <stdio.h>

// Author: Josiah W
// Contributions by Tyler H

int main(int argc, char *argv[]) {
	// Phase 1: lexical analysis

	int c = 0;
	bool first = true;
	grammar *gram = new grammar("grammar.txt");
	symbol token;
	production p;

	while (c != EOF) {
		c = gram->lexan();
		if (!(c <= 90 && c >= 65)) {
			// Not what we expected
			printf("Error: expected non-terminal");
			break;			
		}

		// update our symbol object
		token.name = c;
		token.isTerm = false;

		// Now we figure out what to do with it

		if (first) {
			// First means it is our start symbol
			gram->setStart(token);
			first = false; // now we never repeat this code.

			p.derivations = new symList*[10];
			p.d_count = 0;
			p.non_t = token;
			gram->A->add(token);	

		} else {
			// check if there is already a production for our token
			if (!gram->productionExists(token)) {
				// There isn't, so we're making a new production
				// all non-terminals must have at least one	
				// production, so this is sufficient to check
				p.derivations = new symList*[10];
				p.d_count = 0;
				p.non_t = token;
				gram->A->add(token);							
			} else {
				// We want to load the existing production
				// object into our variable p
				p = gram->getProduction(token);
			}			

		}
		// Whatever the case: we add the following derivation to 
		// the production list under whatever non-terminal we 
		// just read.
		if (gram->lexan() != '-') {
			printf("Expected '-' character");
		}

		if (gram->lexan() != '>') {
			printf("Expected '>' character");
		}
		
		// Now we're reading a production
		// If we've reached this point, we have a production
		// ready to load into with an associated non-terminal

		c = gram->lexan();

		p.derivations[p.d_count] = new symList(3);
		
		while (c != ';') {
			c = gram->lexan();
			
			if (c == '|') {
				// add new derivation and inc d_count
				p.derivations[p.d_count] = new symList(3);
				p.d_count++;
							
			}
			// is it lowercase? [97-122]
			if (c >= 97 && c <= 122) {
				// put it into the terminal list (chris pratt?)
				token.isTerm = true;
				token.name = c;
				printf("doing addnew\n");
				fflush(stdout);
				gram->T->addNew(token);
				printf("did addnew\n");

				// Now we add it to the current production
				p.derivations[p.d_count]->add(token);
				printf("added to derivations list");
				fflush(stdout);

			} else if (c <= 90 && c >= 65) {
				// put it in the non-terminal list
				token.isTerm = false;
				token.name = c;
				gram->A->addNew(token);

				// add it to current production
				p.derivations[p.d_count]->add(token);

			}
		}
		// Add the current production to the production list
		gram->addProduction(p);

		}	
	
	return 0;
}

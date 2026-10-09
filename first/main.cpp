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
	grammar *gram = new grammar(argv[1]);
	symbol token;


	while (c != EOF) {
		production *p = NULL;
		c = gram->lexan();
		if (!(c <= 90 && c >= 65)) {
			// Not what we expected
			if (c == EOF) // check if we are add the end of the file
			{
			}else{
				printf("Error: expected non-terminal \n");
			}
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

			production newp = { .non_t = token, .derivations =  new symList*[10], .d_count = 1};
			gram->A->addNew(token);	
			p = &newp;

		} else {
			// check if there is already a production for our token
			if (!gram->productionExists(token)) {
				// There isn't, so we're making a new production
				// all non-terminals must have at least one	
				// production, so this is sufficient to check
				production newp = { .non_t = token, .derivations =  new symList*[10], .d_count = 1};
				gram->A->addNew(token);	
				p = &newp;
						
			} else {
				// We want to load the existing production
				// object into our variable p
				p = &gram->getProduction(token);
				p->d_count++;
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

		//c = gram->lexan();this caused it to read another line before the first was used elemeniating the first right hand symbol

		p->derivations[p->d_count - 1] = new symList(3);
		
		while (c != ';') {
			c = gram->lexan(); 
			
			if (c == '|') {
				//increment to open up new spot (previous seg fault here)
				p->d_count++;
				// add new derivation and inc d_count
				p->derivations[p->d_count - 1] = new symList(3);
				

			}
			// is it lowercase? [97-122]
			if (c >= 97 && c <= 122) {
				// put it into the terminal list (chris pratt?)
				token.isTerm = true;
				token.name = c;
				
				gram->T->addNew(token);
				
				// Now we add it to the current production
				p->derivations[p->d_count - 1]->add(token);

			} else if (c <= 90 && c >= 65) {
				// put it in the non-terminal list
				token.isTerm = false;
				token.name = c;
				gram->A->addNew(token);

				// add it to current production
				p->derivations[p->d_count - 1]->add(token);


			} else if (c == '&') {
				token.isTerm = true;
				token.name = c;
				gram->T->addNew(token);

				p->derivations[p->d_count - 1]->add(token);
			}
		}
		// Add the current production to the production list
		// if it is new
		if (!gram->productionExists(p->non_t)) {
			gram->addProduction(p);
		}
	}	
	gram->first(); 

	gram->printIt();

	return 0;
}

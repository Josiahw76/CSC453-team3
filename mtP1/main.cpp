// #include "first.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *file = fopen("grammar.txt", "r");
	char c;
	// Process grammar
	for (;;) {
	c = fgetc(file);
		switch (c) {
				case '-':
				fgetc(file); // skip > and ' ' characters
				fgetc(file);
				break;
				case

		}
	}
	// wait, the grammar is deterministic, why am I doing this
	
	return 0;
}

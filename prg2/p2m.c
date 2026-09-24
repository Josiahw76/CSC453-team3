#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2.h"

int
main() {
    int tk;

    myInit();
    while(tk = yylex()) {
	printf("got this: %s\n", yytext);
    }
    dumpSymbolTable();
}

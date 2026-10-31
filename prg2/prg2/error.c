#include <stdio.h>
#include <stdlib.h>
#include "pretty.h"

void error(char *m) {
    //fprintf(stderr, "line %d: %s\n", lineno, m);
    fprintf(stderr, "line %d: %s\n", 0, m);
    exit(1);
}


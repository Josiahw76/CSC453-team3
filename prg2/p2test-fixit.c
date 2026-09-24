#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// Include local header files

#include "p2.h"
#include "teddyBear.h"
#include "sally.h"

/******************************************************************************/

// typedefs

typedef struct nodeT { int key; struct nodeT *left, *right; } NODE_TYPE;

/******************************************************************************/

// Global variables
int global_1 = 100; int global_2 = 200;

float global_float_1 = 100.100; float global_float_2 = 200.200;

NODE_TYPE *root = 0;

/******************************************************************************/

int min(int a, int b) { return(a>b ? b : a); }

/******************************************************************************/

int max(int a, int b) { return(a<b ? b : a); }

/******************************************************************************/
float myfmax(float x, float y) { return(x<y ? y : x); }

/******************************************************************************/

int insertNode(NODE_TYPE **p, int key) { int rc = 0; if (*p) { if ((*p)->key < key) { rc = insertNode(&((*p)->right), key); } else if ((*p)->key > key) { rc = insertNode(&((*p)->left), key); } } else { rc = 1; *p = (NODE_TYPE *)malloc(sizeof(NODE_TYPE)); (*p)->key = key; (*p)->left = 0; (*p)->right = 0; } return(rc);
}

/******************************************************************************/

int main(int argc, char *argv[]) { int myInt1, myInt_2, myInt_3; int rc; float myFloat_1, myFloat_2, myFloat_3; fprintf(stderr, "Size of nodeT is %d", sizeof(NODE_TYPE)); myInt_1 = max(global_1, global_2) - min(global_1, global_2); rc = insertNode(&root, myInt_1); return(rc);
}

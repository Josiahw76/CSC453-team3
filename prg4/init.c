#include "global.h"
#include "mycc.h"

static struct Symbol keywords[] =
{
	{ "do",		DO },
	{ "else",	ELSE },
	{ "float",	FLOAT },
	{ "for",	FOR },
	{ "if",		IF },
	{ "int",	INT },
	{ "main",	MAIN },
	{ "return",	RETURN },
	{ "void",	VOID },
	{ "while",	WHILE },
	{ "break",	BREAK },
	{ NULL,         0 }
};

/* init - populates global symbol table with keywords */
void init()
{
	struct Symbol *k;

	for (k = keywords; k->lexptr; k++)
		insert(k->lexptr, k->token);
}


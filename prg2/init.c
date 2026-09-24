#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretty.h"

void
myInit() {
    installID("if", IF, -1);
    installID("else", ELSE, -1);
    installID("return", RETURN, -1);
    installID("for", FOR, -1);
    installID("while", WHILE, -1);
    installID("do", DO, -1);
    installID("break", BREAK, -1);
    installID("conintue", CONTINUE, -1);
    installID("switch", SWITCH, -1);
    installID("case", CASE, -1);
    installID("default", DEFAULT, -1);
    installID("char", CHAR, -1);
    installID("short", SHORT, -1);
    installID("int", INT, -1);
    installID("long", LONG, -1);
    installID("float", FLOAT, -1);
    installID("double", DOUBLE, -1);
    installID("unsigned", UNSIGNED, -1);
    installID("void", VOID, -1);
    installID("static", STATIC, -1);
    installID("volatile", VOLATILE, -1);
    installID("extern", EXTERN, -1);
    installID("struct", STRUCT, -1);
    installID("typedef", TYPEDEF, -1);
    installID("sizeof", SIZEOF, -1);
}


/* TODO: TO BE COMPLETED */

%{

#include "lex.yy.h"
#include "global.h"
static struct ClassFile cf;

%}

/* declares YYSTYPE type of attribute for all tokens and nonterminals */
%union
{ Symbol *sym;  /* token value yylval.sym is the symbol table entry of an ID */
  unsigned num; /* token value yylval.num is the value of an int constant */
  float flt;    /* token value yylval.flt is the value of a float constant */
  char *str;    /* token value yylval.str is the value of a string constant */
  unsigned loc; /* location of instruction to backpatch */
}

/* Declare ID token and its attribute type 'sym' */
%token <sym> ID

/* Declare INT tokens (8 bit, 16 bit, 32 bit) and their attribute type 'num' */
%token <num> INT8 INT16 INT32

/* Declare FLT token (not used in this assignment) */
%token <flt> FLT

/* Declare STR token (not used in this assignment) */
%token <str> STR

/* Declare tokens for keywords */
/* Note: install_id() returns Symbol* for both keywords and identifiers */
%token <sym> BREAK DO ELSE FOR IF RETURN WHILE

/* Declare operator tokens */
/* TODO: TO BE COMPLETED WITH ASSOCIATIVITY AND PRECEDENCE DECLARATIONS */
%token PA NA TA DA MA AA XA OA LA RA OR AN EQ NE LE GE LS RS AR PP NN

/* Declare attribute types for marker nonterminals, such as L M and N */
/* TODO: TO BE COMPLETED WITH ADDITIONAL NONMARKERS AS NECESSARY */
%type <loc> L M N

%%

stmts   : stmts stmt
        | /* empty */
        ;

stmt    : ';'
        | expr ';'      { emit(pop); /* do not leave a value on the stack */ }
        | IF '(' expr ')' stmt
                        { /* TODO: TO BE COMPLETED */ error("if-then not implemented"); }
        | IF '(' expr ')' stmt ELSE stmt
                        { /* TODO: TO BE COMPLETED */ error("if-then-else not implemented"); }
        | WHILE '(' expr ')' stmt
                        { /* TODO: TO BE COMPLETED */ error("while-loop not implemented"); }
        | DO stmt WHILE '(' expr ')' ';'
                        { /* TODO: TO BE COMPLETED */ error("do-while-loop not implemented"); }
        | FOR '(' expr ';' expr ';' expr ')' stmt
                        { /* TODO: TO BE COMPLETED */ error("for-loop not implemented"); }
        | RETURN expr ';'
                        { emit(istore_2); /* return val goes in local var 2 */ }
        | BREAK ';'
                        { /* TODO: BONUS!!! */ error("break not implemented"); }
        | '{' stmts '}'
        | error ';'     { yyerrok; }
        ;

expr    : ID   '=' expr { emit(dup); emit2(istore, $1->localvar); }

	/* Note: May not need to add in an emit(iload, $1->localvar); */
	/* Compound assignment operators: emit the value in ID, */
	/* do the operation, dupe it, put back to id. */
	/* Leaves the id on the stack for subsequent operations */
        | ID   PA  expr { emit(iload, $1->localvar); emit(iadd); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   NA  expr { emit(iload, $1->localvar); emit(isub); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   TA  expr { emit(iload, $1->localvar); emit(imul); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   DA  expr { emit(iload, $1->localvar); emit(idiv); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   MA  expr { emit(iload, $1->localvar); emit(irem); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   AA  expr { emit(iload, $1->localvar); emit(iand); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   XA  expr { emit(iload, $1->localvar); emit(ixor); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   OA  expr { emit(iload, $1->localvar); emit(ior);
				emit(dup); emit2(istore, $1->localvar) }
        | ID   LA  expr { emit(iload, $1->localvar); emit(ishl); 
				emit(dup); emit2(istore, $1->localvar) }
        | ID   RA  expr { emit(iload, $1->localvar); emit(ishr); 
				emit(dup); emit2(istore, $1->localvar) }

	/* evaluates both terms. True short-circuit evaluation needs a marker non-terminal */
        | expr OR  expr { emit3(ifne, pc+4); emit3(ifne, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr AN  expr { emit3(ifeq, pc+4); emit3(ifeq, pc+3); emit(iconst_1); emit3(goto_, pc+2); emit(iconst_0); }

        | expr '|' expr { emit(ior); }
        | expr '^' expr { emit(ixor); }
        | expr '&' expr { emit(iand); }

	/* If the evaluation is true, branch. Otherwise, flow continues. */
	/* True should emit 1, false 0, so use offsets and jumps to */
	/* emit the correct one. */
        | expr EQ  expr { emit3(if_icmpeq, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr NE  expr { emit3(if_icmpne, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr '<' expr { emit3(if_icmplt, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr '>' expr { emit3(if_icmpgt, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr LE  expr { emit3(if_icmple, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | expr GE  expr { emit3(if_icmpge, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
	/* comparisons */

        | expr LS  expr { emit(ishl); }
        | expr RS  expr { emit(ishr); }
        | expr '+' expr { emit(iadd); }
        | expr '-' expr { emit(isub); }
        | expr '*' expr { emit(imul); }
        | expr '/' expr { emit(idiv); }
        | expr '%' expr { emit(irem); }

	/* If true, emit false. If false, emit true. ifeq flows forward if value is 1, jumps if 0. */
        | '!' expr      { emit3(ifeq, pc+3); emit(iconst_0); emit3(goto_, pc+2); emit(iconst_1); }
        | '~' expr      { /* TODO: TO BE COMPLETED */ error("~ operator not implemented"); }	 { emit(); }
        | '+' expr %prec '!' /* '+' at same precedence level as '!' */ { /* do nothing */ }
        | '-' expr %prec '!' /* '-' at same precedence level as '!' */ { emit(ineg); }
        | '(' expr ')'
        | '$' INT8      { emit(aload_1); emit2(bipush, $2); emit(iaload); }
        | PP ID         { $2->localvar = $2->localvar + 1; emit($2->localvar); }
        | NN ID         { $2->localvar = $2->localvar - 1; emit($2->localvar); }
        | ID PP         { emit($2->localvar); $2->localvar = $2->localvar + 1; }
        | ID NN         { emit($2->localvar); $2->localvar = $2->localvar - 1; }
        | ID            { emit2(iload, $1->localvar); }
        | INT8          { emit2(bipush, $1); }
        | INT16         { emit3(sipush, $1); }
        | INT32         { emit2(ldc, constant_pool_add_Integer(&cf, $1)); }
	| FLT		{ error("float constant not supported in Pr3"); }
	| STR		{ error("string constant not supported in Pr3"); }
        ;

L       : /* empty */   { $$ = pc; }
        ;

M       : /* empty */   { $$ = pc;	/* location of inst. to backpatch */
			  emit3(ifeq, 0);
			}
        ;

N       : /* empty */   { $$ = pc;	/* location of inst. to backpatch */
			  emit3(goto_, 0);
			}
        ;

/* TODO: TO BE COMPLETED WITH ADDITIONAL NONMARKERS AS NEEDED */

%%

int main(int argc, char **argv)
{
	int index1, index2, index3;
	int label1, label2;

	// set up new class file structure
	init_ClassFile(&cf);

	// class has public access
	cf.access = ACC_PUBLIC;

	// class name is "Code"
	cf.name = "Code";

	// no fields
	cf.field_count = 0;

	// one method
	cf.method_count = 1;

	// allocate array of methods (just one "main" in our example)
	cf.methods = (struct MethodInfo*)malloc(cf.method_count * sizeof(struct MethodInfo));

	if (!cf.methods)
		error("Out of memory");

	// method has public access and is static
	cf.methods[0].access = (enum access_flags)(ACC_PUBLIC | ACC_STATIC);

	// method name is "main"
	cf.methods[0].name = "main";

	// method descriptor of "void main(String[] arg)"
	cf.methods[0].descriptor = "([Ljava/lang/String;)V";

	// max operand stack size of this method
	cf.methods[0].max_stack = 100;

	// the number of local variables in the local variable array
	//   local variable 0 contains "arg"
	//   local variable 1 contains "val"
	//   local variable 2 contains "i" and "result"
	cf.methods[0].max_locals = 100;

	// set up new bytecode buffer
	init_code();
	
	// generate prologue code

/*LOC*/ /*CODE*/			/*SOURCE*/
/*000*/	emit(aload_0);
/*001*/	emit(arraylength);		// arg.length
/*002*/	emit2(newarray, T_INT);
/*004*/	emit(astore_1);			// val = new int[arg.length]
/*005*/	emit(iconst_0);
/*006*/	emit(istore_2);			// i = 0
	label1 = pc;			// label1:
/*007*/	emit(iload_2);
/*008*/	emit(aload_0);
/*009*/	emit(arraylength);
	label2 = pc;
/*010*/	emit3(if_icmpge, PAD);		// if i >= arg.length then goto label2
/*013*/	emit(aload_1);
/*014*/	emit(iload_2);
/*015*/	emit(aload_0);
/*016*/	emit(iload_2);
/*017*/	emit(aaload);			// push arg[i] parameter for parseInt
	index1 = constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
/*018*/	emit3(invokestatic, index1);	// invoke Integer.parseInt(arg[i])
/*021*/	emit(iastore);			// val[i] = Integer.parseInt(arg[i])
/*022*/	emit32(iinc, 2, 1);		// i++
/*025*/	emit3(goto_, label1 - pc);	// goto label1
	backpatch(label2, pc - label2);	// label2:

	// end of prologue code

	init();

	if (argc > 1)
		if (!(yyin = fopen(argv[1], "r")))
			error("Cannot open file for reading");

	if (yyparse() || errnum > 0)
		error("Compilation errors: class file not saved");

	fprintf(stderr, "Compilation successful: saving %s.class\n", cf.name);

	// generate epilogue code

	index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
/*036*/	emit3(getstatic, index2);	// get static field System.out of type PrintStream
/*039*/	emit(iload_2);			// push parameter for println()
	index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
/*040*/	emit3(invokevirtual, index3);	// invoke System.out.println(result)
/*043*/	emit(return_);			// return

	// end of epilogue code

	// length of bytecode is in the emitter's pc variable
	cf.methods[0].code_length = pc;
	
	// must copy code to make it persistent
	cf.methods[0].code = copy_code();

	if (!cf.methods[0].code)
		error("Out of memory");

	// save class file to "Calc.class"
	save_classFile(&cf);

	return 0;
}


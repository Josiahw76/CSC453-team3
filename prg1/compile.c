#include "global.h"
#include "javaclass.h"
#include "bytecode.h"

#define MAX_SIZE 127

struct ClassFile cf;
int index1, index2, index3;
int label1, label2;

int tk; // lookahead token
int stackDepth;

int retLoc[2*MAX_SIZE];
int numRets = 0;

extern int assign_var_index(int tokenval);
extern int match(int token); 
extern void stmt();
extern void opt_stmts();
extern void expr();
extern void term();
extern void moreterms();
extern void factor();
extern void morefactors();

//*******************************************************************************

void
java_preamble() {
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

    // method has public access and is static
    cf.methods[0].access = ACC_PUBLIC | ACC_STATIC;

    // method name is "main"
    cf.methods[0].name = "main";

    // method descriptor of "void main(String[] arg)"
    cf.methods[0].descriptor = "([Ljava/lang/String;)V";

    // max operand stack size of this method
    cf.methods[0].max_stack = MAX_SIZE;

    // the number of local variables in the local variable array
    //   local variable 0 contains "arg"
    //   local variable 1 contains "val"
    //   local variable 2 contains "i" and "result"
    cf.methods[0].max_locals = 3 + MAX_SIZE;

    // set up new bytecode buffer
    init_code();
    
    // generate code
/*LOC*/
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

}

//*******************************************************************************

void
java_postamble() {

    for (int i = 0; i < numRets; i++) {
	backpatch(retLoc[i], pc - retLoc[i]);
    }
    index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
/*036*/	emit3(getstatic, index2);	// get static field System.out of type PrintStream
/*039*/	emit(iload_2);			// push parameter for println()
    index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
/*040*/	emit3(invokevirtual, index3);	// invoke System.out.println(result)
/*043*/	emit(return_);			// return

    // length of bytecode is in the emmiter's pc variable
    cf.methods[0].code_length = pc;
    
    // must copy code to make it persistent
    cf.methods[0].code = copy_code();

    // save class file to "Code.class"
    save_classFile(&cf);
}

//*******************************************************************************

int
match(int token) {
    int rc = 0;  // in case we don't have a match, we return "false"

    if (token == tk) {
	rc = 1;
	tk = lexan(); // get next token
    }

    return(rc);
}

//*******************************************************************************

void
stmt() {
    int var_index; // This records the identifiers symbol table
    int loc = -1; //backpatch target for WHILE's exit loop
    int if_loc = -1; //backpatch target for IF's condition loop
    int else_loc = -1; //backpatch target for IF's skip-else jump

    switch (tk) {  // Set look ahead token tk that is set in main
		
	case LEFT_CURLY:

	    match(LEFT_CURLY); // if tk see's the left curly bracket we know to use this case and advance the lexer
	    opt_stmts();		// this should recursivly parse through zero or more statements and everything in the braces

	    if (!match(RIGHT_CURLY)) { // Tries to consume last brace and will return error if not there

		error("Expected closing curly brace");

	    }

	    break;
	
	case ID:

	    var_index = symtable[tokenval].var_index; // Look up the identifiers frame-slot number before calling match

	    if (var_index < 0) { // checks if what we typed is a reserved word and not a real variable

		error("Attempting to use keyword as variable");

	    } else if (var_index == 0) {

		var_index = assign_var_index(tokenval); // initializes and  

	    }
	    // else case already taken care of, just overwrite existing variable
	    
	    match(ID); // takes in identifier and advancing tk


	    if (!match(EQ)) { // If the next token isnt a = it is invalid
		error("Expected assignment operator");
	    }

	    expr(); // parse and emit bycode for the right hand side 

	    if (stackDepth >= 1) {

		emit2(istore, var_index); // pop the value from expr() off the stack and store it into the variables frameslot
		stackDepth--;

	    } else {	// If expr() somehow produced nothing

		error("No rvalue for assignment operator");
	    }

	    if (!match(';')) { // requires the terminating sysmbol ;
		error("Expected ';'");
	    }

	    break;
	
	case IF:
	    match(IF);

	    if (!match('(')) { // check for the opening bracket
		error("Mising parenthesis");
	    }

	    expr(); // parse and emit the condition

	    if (!match(')')) { // check ending bracket
		error("Mising parenthesis");
	    }

	    emit(iconst_0); // push 0 so the condition can compare something

	    if_loc = pc; // record the address where the next instruction is going to be emmited at for backpatch
	    emit3(if_icmpeq, 0); // pop the condition value and the 0 and compare them if equal branch
		
	    stmt();

		else_loc = pc; // record the address for where the next instruction is be jumped to 
	    emit3(goto_, 0); // this alows the then branch skip over the else branch once its done executing

	    backpatch(if_loc, pc - if_loc); // since we have started the else branch we can now go back and replace 0 with pc - if_loc

	    if (!match(ELSE)) { // checks to make sure the next word is else
		error("Expected 'else'");
	    }

	    stmt();

	    backpatch(else_loc, pc - else_loc); //go back and replace 0 with pc - if_loc

	    break;
	
	case WHILE:

	    match(WHILE);

	    if (!match('(')) { // require and check the first charactor is opening bracket
		error("Mising parenthesis");
	    }

	    int test_loc = pc; // record the starting address

	    expr(); // parse and emit

	    if (!match(')')) { // check ending bracket
		error("Mising parenthesis");
	    }

	    emit(iconst_0); // push 0 again so there is something to be compared
	    loc = pc; // store the address the next instruction is going to be emited at for backpatch later
	    emit3(if_icmpeq, 0); //pop the condition value and the 0 compare the values and if equal branch

	    stmt();// parse and emit the loops body code

	    emit3(goto_, test_loc-pc); //jump back to the top of the loop
	    backpatch(loc, pc-loc); // now that pc is passed goto_ fix if_icmpeq by replaceing 0 with pc -loc

	    break;
	
	case RET:

	    match(RET);

	    expr(); //parse and emit the returns value code

	    if (stackDepth >= 1) { //make sure expr() gave something back

		emit(istore_2);// pop the value off the stack and store it in local variable slot 2
		retLoc[numRets] = pc; // record the address the next instruction is going to be emitted at
		emit3(goto_, retLoc[numRets]); // 
		numRets++; //increment to the next free spot so the next return statement gets its own entry

	    } else { //if the expr() left nothing on the stack 
		error("No value to return, stack empty");
	    }

		 if (!match(';')) {     // require terminating statement ;     
       	 error("Expected ';'");
   		 }     

	    break;
	
	default:
	    error("Unexpected token, expected statement");
	    break;
    }
}

//*******************************************************************************

void
opt_stmts() {
    // to be completed
    // grammar = stmt opt_stmts | nothing
    stmt();

    // Match's last line assigns the value of lexan() to tk.
    // If lexan finds EOF, it assigns DONE to tk.
    // Therefore, continue until tk is DONE.
    if (tk != DONE) {
    	opt_stmts();
    }
}

//*******************************************************************************

void
expr() {
    // to be completed
    term();
    moreterms(); // This is not called anywhere else except moreterms
}

//*******************************************************************************

void
term() {
    // This should just work?
    factor(); 
    morefactors();
}

//*******************************************************************************

void
moreterms() {
	// printf("entered more_terms"); // DEBUG
    if (!(tk==';' || tk==')')) {
	switch (tk) {
	    case PLUS:
		match(PLUS);
		term();
		if (stackDepth < 2) {
		    error("Not enough operands for '+'");
		}
		emit(iadd);
		stackDepth--;
		moreterms();
		break;
	    
	    case MINUS:
		// Josiah
		// Essentially identical to the PLUS case, not much
		// original work was done here
		match(MINUS);
		term();
		if (stackDepth < 2) {
		    error("Not enough operands for '-'");
		}
		emit(isub);
		stackDepth--;
		moreterms();
		break;

	    default:
		error("Expected '+' or '-'");
	}
    }
}

//*******************************************************************************

void
morefactors() {
    if (!(tk=='+' || tk=='-' || tk==';' || tk==')')) {
	switch (tk) {
	    case MUL:
		// to be completed
		// Perform mult. using the steps from prior defined operations

		morefactors();
		break;
	    
	    // to be completed
	    // Division and Modulo operators go here, two extra cases
	    
	    default:
		error("Expected '*', '/' or '%'");
	}
    }
}

//*******************************************************************************

void
factor() {
    int var_index = -1;

    switch (tk) {
	case LEFT_PAREN:
	    match('(');
	    expr();
	    if (!match(')')) {
		error("Missing close parenthesis");
	    }
	    break;
	
	case MINUS:
	    match('-');
	    if (stackDepth < 1) {
		error("Not enough operands for negation");
	    }
	    factor();

	    emit(ineg);
	    break;
	
	case INT8:
	    emit2(bipush, tokenval);
	    stackDepth++;

	    match(INT8);
	    break;
	
	case INT16:
	    emit3(sipush, tokenval);
	    stackDepth++;

	    match(INT16);
	    break;
	
	case INT32:
	    emit2(ldc, constant_pool_add_Integer(&cf, tokenval));
	    stackDepth++;

	    match(INT32);
	    break;
	
	case ID:
	    var_index = symtable[tokenval].var_index;
	    if (var_index < 0) {
		error("Keywords are not valid lvalues");
	    } else if (var_index == 0) {
		error("Variable does not exist");
	    } else {
		// Josiah - aload followed by index indicates that the value
		// is to be loaded from the localvar table at that location
		emit2(aload, var_index);
		stackDepth++;
	    }

	    match(ID);
	    break;
	
	case ARG:
	    // Josiah
	    match(ARG);

	    match('[');
	    emit(aload_1);
	    emit2(bipush, tokenval); // Problematic bipush here
				     // amitting -1 consistently

	    match(INT8);

	    if (!match(']')) {
		error("Missing close bracket");
	    }

	    stackDepth++;
	    emit(iaload);

	    break;

	default:
	    error("Expected a factor");
	    break;
    }
}

//*******************************************************************************

int
main() {
    init();

    java_preamble();

    tk = lexan();

    if (!(tk == DONE || tk == EOF)) {
	stmt();
    }

    java_postamble();

    // Useful to do the following when debugging
    //dumpSumbolTable();

    return 0;
}

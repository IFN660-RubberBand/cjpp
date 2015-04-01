%{
    #include <stdio.h>
    #include <string.h>	
    int yylex(void);
    extern void yyerror(char *message);
	int yywrap()
{
	return 1;
}
%}
/* equality operators */
%token NUMBER
%token HEXNUMBER
%token IDENTIFIER
%token SEMICOLON
%token COLON
%token COMMA
%token POINT
%token QUESTION

		/* operators */
%left PLUS
%left INC
%left MINUS
%left DEC
%left MULTIPLY
%left DIVIDE
%left MOD

		/* all assignments */ 
%right ASSIGN
%right ASSPLUS
%right ASSMINUS
%right ASSMULTIPLY	 
%right ASSDIVIDE	
%right ASSMOD		
%right ASSBITXOR
%right ASSBITOR		
%right ASSBITAND
%right ASSLSHIFT
%right ASSRSHIFT
%right ASSLRSHIFT

		/* Comparison opeartors */
%right GTR
%right NEQ
%right NIDENT
%right LEQ
%right GEQ

		/* shift operation */
%left LSHIFT
%left RSHIFT
%left LRSHIFT

		/* logic operator */ 
%right NOT         /* not sure if really right associative */
%left  OR		   /* definitely left for lazy evaluation */
%left  AND	

		/* bitwise operator */ 
%left BITXOR		/*  not sure at all about associativity */
%left BITOR		
%left BITAND
%right BITNOT

		/* Equality Operators */
		
%left EQUALS
%left NOTEQUALS
%left STRICTEQUALS
%left STRICTNOTEQUALS

		/* Comma Operator */

%left COMMA 

			/* Conditional Operator*/

%right CONDITION

		/* brackets */
%token LPAREN		"(" 
%token RPAREN		")"
%token LBRACK		"["
%token RBRACK		"]"
%token LCURLY		"{"
%token RCURLY		"}"
		
		/* keywords */
%token BREAKSYM		"break"
%token CASESYM		"case"
%token CATCHSYM		"catch"	
%token CONTSYM		"continue"
%token DEBUGSYM		"debugger"
%token DEFAULTSYM	"default"
%token DELSYM		"delete"
%token DOSYM		"do"
%token ELSESYM		"else"
%token FINALSYM		"finally"
%token FORSYM		"for"
%token FUNCSYM		"function"
%token IFSYM		"if"
%token INSYM		"in"
%token INSTSYM		"instanceof"
%token NEWSYM		"new"
%token RETURNSYM	"return"
%token SWITCHSYM	"switch"
%token THISSYM		"this"
%token THROWSYM		"throw"
%token TRYSYM		"try"
%token TYPEOFSYM	"typeof"
%token VARSYM		"var"
%token VOIDSYM		"void"
%token WHILESYM		"while"
%token WITHSYM		"with"
%left EQUALS
%left NOTEQUALS
%left STRICTEQUALS
%left STRICTNOTEQUALS
%%
program:   
      equalexp equalexpnoin program		
   	|
   	;
/* Equality operators 11.9*/

equalexp:
	relationexpr
	|equalexp EQUALS relationexpr
	|equalexp NOTEQUALS relationexpr
	|equalexp STRICTEQUALS relationexpr
	|equalexp STRICTNOTEQUALS relationexpr
	;
	
equalexpnoin:
	relationexprnoin
	|equalexpnoin EQUALS relationexprnoin
	|equalexpnoin NOTEQUALS relationexprnoin
	|equalexpnoin STRICTEQUALS relationexprnoin
	|equalexpnoin STRICTNOTEQUALS relationexprnoin
	;
	
/* BitWise Operators 11.10 */

bitandexp:
	equalexp
	bitandexp BITAND equalexp
	;
	
bitandexpnoin:
	equalexpnoin
	bitandexpnoin BITAND equalexpnoin
	;
	
bitxorexp:
	bitandexp
	bitxorexp BITXOR bitandexp
	;
	
bitxorexpnoin:
	bitandexpnoin
	bitxorexpnoin BITXOR bitandexpnoin
	;

bitorexp:
	bitxorexp
	bitorexp BITOR bitxorexp
	;

	
bitorexpnoin:
	bitxorexpnoin
	bitorexpnoin BITOR bitxorexpnoin
	;

	/* Binary Logical Operators 11.11 */

logicandexp:
	bitorexp
	logicandexp AND bitorexp
	;
	
logicandexpnoin:
	bitorexpnoin
	logicandexpnoin AND bitorexpnoin
	;

logicorexp:
	logicandexp
	logicorexp OR logicandexp
	;
	
logicorexpnoin:
	logicandexpnoin
	logicorexpnoin OR logicandexpnoin
	;

	/* Conditional Operator 11.12*/


conditionexp:
	logicorexp
	logicorexp CONDITION assignexp CONDITION assignexp
	;
	
conditionexpnoin:
	logicorexpnoin
	logicorexpnoin CONDITION assignexp CONDITION assignexpnoin
	;
	
/* Assignmnet Operators 11.13*/

assignexp:
	conditionexp
	lefthandsideexpression ASSIGN assignexp
	lefthandsideexpression assignop assignexp
	;
	
assignexpnoin:
	conditionexpnoin
	lefthandsideexpression ASSIGN assignexpnoin
	lefthandsideexpression assignop assignexpnoin
	;
	
assignop: one of
	ASSMULTIPLY ASSDIVIDE ASSMOD ASSPLUS ASSMINUS ASSLSHIFT ASSRSHIFT ASSLRSHIFT ASSBITAND ASSBITXOR ASSBITOR
	;

/* Comma Operator 11.14*/

exp:
	assignexp
	exp COMMA assignexp
	;
	
expnoin:
	assignexpnoin
	expnoin COMMA assignexpnoin
	;
%%
main()
{
	yyparse();
	return 0;
}

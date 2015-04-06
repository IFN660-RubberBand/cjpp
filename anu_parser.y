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

equalexp:
	relationexpr					{printf("Equal expression");}
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

%%

main()
{
	yyparse();
	return 0;
}
	

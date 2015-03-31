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

		/* relational operators */
%left LESSTHAN
%left GREATERTHAN
%left LESSTHANEQUAL
%left GREATERTHANEQUAL

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
%token FINALSYM		"final"
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

%%

program: 
	statement program
	|
	;

statement:
	expr SEMICOLON 		{ printf("%s\n", $1); }
	| IDENTIFIER ASSIGN expr SEMICOLON
	| VARSYM IDENTIFIER ASSIGN expr SEMICOLON
	| VARSYM IDENTIFIER SEMICOLON
	| WHILESYM LPAREN expr RPAREN LCURLY program RCURLY
	;

lefthandsideexpr:
	IDENTIFIER 
	expr:
	NUMBER 			{ printf("%d", $1); }
	| HEXNUMBER
	| IDENTIFIER
	| expr PLUS expr	
	| expr MINUS expr			
	| expr MULTIPLY expr
	| expr DIVIDE expr
	| expr MOD expr
	| expr LSHIFT expr
	| expr RSHIFT expr
	| expr LRSHIFT expr
	| LPAREN expr RPAREN
	| unaryexpr
	;

		/* 11.3 - Postfix Expressions */
postfixexpr:
	lefthandsideexpr
	| lefthandsideexpr DEC
	| lefthandsideexpr INC
	;	
		/* END OF 11.3 - Postfix Expressions */
	
		/* 11.4 - Unary Expressions */	
unaryexpr:
	postfixexpr
	| DELSYM unaryexpr
	| VOIDSYM unaryexpr
	| TYPEOFSYM unaryexpr
	| INC unaryexpr
	| DEC unaryexpr
	| PLUS unaryexpr
	| MINUS unaryexpr
	| BITNOT unaryexpr
	| NOT unaryexpr
	;	
		/* END OF 11.4 - Unary Expressions */
	
		/* 11.8 - Relational Operators */	
relationexpr:
	shiftexpr
	| relationexpr LESSTHAN shiftexpr
	| relationexpr GREATERTHAN shiftexpr
	| relationexpr LESSTHANEQUAL shiftexpr
	| relationexpr GREATERTHANEQUAL shiftexpr
	| relationexpr INSTSYM shiftexpr
	| relationexpr INSYM shiftexpr
	;
	
relationexprnoin:
	shiftexpr
	| relationexprnoin LESSTHAN shiftexpr
	| relationexprnoin GREATERTHAN shiftexpr
	| relationexprnoin LESSTHANEQUAL shiftexpr
	| relationexprnoin GREATERTHANEQUAL shiftexpr
	| relationexprnoin INSTSYM shiftexpr
	;
		/* END OF 11.8 - Relational Operators */
		
primaryexpr: 
	THISSYM
	| IDENTIFIER 
	;

		/* 11.2 - Left-Hand-Side-Expressions */
memberexpression:
	primaryexpression
	| functionexpression
	| memberexpression LBRACK expression RBRACK
	| memberexpression POINT identifiername
	| NEWSYM memberexpression arguments
	;
	
newexpression:
	memberexpression
	| NEWSYM newexpression
	;
	
callexpression:
	memberexpression arguments
	| callexpression arguments
	| callexpression LBRACK expression RBRACK
	| callexpression POINT identifiername
	;
	
arguments:
	LPAREN RPAREN
	| LPAREN argumentlist RPAREN
	;

argumentlist:
	assignmentexpression
	| argumentlist COMMA assignmentexpression
	;

leftHandSideExpression :
	newexpression
	| callexpression
	;
		/* END OF 11.2 - Left-Hand-Side Expressions */
		
		/* 11.5 - Multiplicative Operators */
multiexpr:
	unaryexpr
	| multiexpr MULTIPLY unaryexpr
	| multiexpr DIVIDE unaryexpr
	| multiexpr MOD unaryexpr
	;
	/* END OF 11.5 - Multiplicative Operators */
	
		/* 11.6 - Additive Operators */
addexpr:
	multiexpr
	| addexpr PLUS multiexpr
	| addexpr MINUS multiexpr
	;
		/* END OF 11.6 - Additive Operators */
	
		/* 11.7 - Bitwise Shift Operators */
shiftexpr:
	addexpr
	| shiftexpr LSHIFT addexpr
	| shiftexpr RSHIFT addexpr
	| shiftexpr LRSHIFT addexpr
	;		
	/* END OF 11.7 - Bitwise Shift Operators */
	
%%

main()
{
	yyparse();
	return 0;
}

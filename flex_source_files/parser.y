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
%left INSTANCEOF
%left IN

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

	/* literals */
%token NULL 		"null"
%token TRUE 		"true"
%token FALSE 		"false"
%token STRING

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

postfixexpr:
	lefthandsideexpr
	| lefthandsideexpr DEC
	| lefthandsideexpr INC
	;

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

/*
relationexpr:
	shiftexpr
	|relationexpr LESSTHAN shiftexpr
	|relationexpr GREATERTHAN shiftexpr
	|relationexpr LESSTHANEQUAL shiftexpr
	|relationexpr GREATERTHANEQUAL shiftexpr
	|relationexpr INSTANCEOF shiftexpr
	|relationexpr IN shiftexpr
	;
	
relationexprnoin:
	shiftexpr
	|relationexprnoin LESSTHAN shiftexpr
	|relationexprnoin GREATERTHAN shiftexpr
	|relationexprnoin LESSTHANEQUAL shiftexpr
	|relationexprnoin GREATERTHANEQUAL shiftexpr
	|relationexprnoin INSTANCEOF shiftexpr
	;
*/

nullliteral:
	NULL
	;

booleanliteral:
	TRUE
	| FALSE
	;

decimalliteral:
	NUMBER
	;

hexintegerliteral:
	HEXNUMBER
	;

numericliteral:
	decimalliteral
	| hexintegerliteral
	;

stringliteral:
	STRING
	;

regularexpressionliteral:
	;

literal:
	nullliteral 
	| booleanliteral
	| numericliteral
	| stringliteral
	| regularexpressionliteral
	;

elison:
	COMMA
	| elison COMMA
	;

elementlist:
	elison assignmentexpression
	| assignmentexpression
	| elementlist COMMA elison assignmentexpression
	| elementlist assignmentexpression
	;

arrayliteral:
	LBRACK elison RBRACK
	| LBRACK RBRACK
	| LBRACK elementlist RBRACK
	| LBRACK elementlist COMMA elison RBRACK
	| LBRACK elementlist COMMA RBRACK
	;

propertyname: 
	identifiername
	| stringliteral
	| numericliteral
	;

propertysetparameterlist:
	IDENTIFIER
	;

propertyassignment:
	propertyname COLON assignmentexpression
	| IDENTIFIER propertyname LPAREN RPAREN LCURLY functionbody RCURLY
	| IDENTIFIER propertyname LPAREN propertysetparameterlist RPAREN LCURLY functionbody RCURLY
	;

propertynameandvaluelist:
	propertyassignment
	| propertynameandvaluelist COMMA propertyassignment
	;

objectliteral:
	LCURLY RCURLY
	| LCURLY propertynameandvaluelist RCURLY
	| LCURLY propertynameandvaluelist COMMA RCURLY
	;

primaryexpr: 
	THISSYM
	| IDENTIFIER 
	| literal
	| arrayliteral
	| objectliteral
	;

%%

main()
{
	yyparse();
	return 0;
}

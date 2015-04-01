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

	/* literals */
%token NULL 		"null"
%token TRUE 		"true"
%token FALSE 		"false"
%token STRING

%%
keyword:
	BREAKSYM		
 	| CASESYM		
	| CATCHSYM			
	| CONTSYM		
	| DEBUGSYM		
 	| DEFAULTSYM	
	| DELSYM		
	| DOSYM			
	| ELSESYM		
	| FINALSYM		
	| FORSYM		
	| FUNCSYM		
	| IFSYM			
	| INSYM			
	| INSTSYM		
	| NEWSYM		
	| RETURNSYM		
	| SWITCHSYM	
	| THISSYM		
	| THROWSYM		
	| TRYSYM		
	| TYPEOFSYM	
	| VARSYM		
	| VOIDSYM		
	| WHILESYM		
	| WITHSYM		
	| NULL
	| TRUE
	| FALSE
	;
	


identifiername:
	IDENTIFIER
	| keyword
	;



		/* 14 - Program */
program:
	sourceelements
	| 
	;
	
sourceelements:
	sourceelement
	| sourceelements sourceelement
	;

sourceelement:
	Statement
	| functiondeclaration
	;
		/* END OF 14 - Program */
		
		/* 13 - Function Definitions */
functiondeclaration :
	FUNCSYM IDENTIFIER LPAREN RPAREN LCURLY functionbody RCURLY
	| FUNCSYM IDENTIFIER LPAREN formalparameterlist RPAREN LCURLY functionbody RCURLY
	;
	
functionexpression :
	FUNCSYM IDENTIFIER LPAREN formalparameterlist RPAREN LCURLY functionbody RCURLY
	| FUNCSYM IDENTIFIER LPAREN  RPAREN LCURLY functionbody RCURLY
	| FUNCSYM LPAREN formalparameterlist RPAREN LCURLY functionbody RCURLY
	| FUNCSYM LPAREN RPAREN LCURLY functionbody RCURLY
	;

formalparameterlist :
	| IDENTIFIER
	| formalparameterlist COMMA IDENTIFIER
	;

functionbody :
	sourceelements
	|
	;	
		/* END OF 13 - Function Definitions */

		/* 11.3 - Postfix Expressions */
postfixexpr:
	lefthandsideexpression
	| lefthandsideexpression DEC
	| lefthandsideexpression INC
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

		/* 11.1 - Primary Expressions */
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

primaryexpression: 
	THISSYM
	| IDENTIFIER 
	| literal
	| arrayliteral
	| objectliteral
	;
		/* END OF 11.1 - Primary Expressions */

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

lefthandsideexpression:
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
	
		
/* All Statements */    

Statement:
	|StatementBlock
	|EmptyStatement		
	|VariableStatement
	|IfStatement	
	|SwitchStatement
	|LabelledStatement
	|ThrowStatement
	|TryStatement
	|DebuggerStatement
	
		/* 12.6 - Iteration Statements */
iterationstatement:
	DOSYM Statement WHILESYM LPAREN expression RPAREN SEMICOLON
	| WHILESYM LPAREN expression RPAREN  Statement 
	| FORSYM LPAREN  expression SEMICOLON expression SEMICOLON expression RPAREN Statement
	| FORSYM LPAREN VARSYM VariableDeclarationList SEMICOLON expression SEMICOLON expression RPAREN Statement
	| FORSYM LPAREN expression INSYM expression RPAREN Statement
	| FORSYM LPAREN VARSYM VariableDeclaration INSYM expression RPAREN Statement
	;
		/* END OF 12.6 - Iteration Statements */

		/* 12.7 - Continue Statement */
continuestatement:
	CONTSYM IDENTIFIER SEMICOLON
	;

/* End of statements */

/* Statment Block */

StatementBlock: 
	|LCURLY StatementList RCURLY						{printf("\t \"Statement block\"\t");}
	;

StatementList:
	|Statement
	|StatementList Statement
	;
		/* END OF 12.7 - Continue Statement */

		/* 12.8 - Break Statement */
breakstatement:
	BREAKSYM IDENTIFIER SEMICOLON
	;
		/* END OF 12.8 - Break Statement */

		/* 12.9 - Return Statement */
returnstatement:
	RETURNSYM expression SEMICOLON
	;
		/* END OF 12.9 - Return Statement */

/* End of Statment Block */

/* Empty Statement */

EmptyStatement:
	|SEMICOLON		        					{printf("\t \"Empty Statement\"\t");}
	;	

/* End of Empty Statement */
		/* 12.10 - With Statement */
withstatement:
	WITHSYM LPAREN expression RPAREN Statement
	;
		/* END OF 12.10 - With Statement */
/*
lineterminator:
	[r\n\u2028\u2029]
	;
*/
/* Variable Statement */

VariableStatement: 		
	|VARSYM VariableDeclarationList SEMICOLON				{printf("\t \"Variable Statement\"\t");}
	;

VariableDeclarationList:
	|VariableDeclaration
	|VariableDeclarationList COMMA VariableDeclaration
	;

VariableDeclaration:
	|IDENTIFIER 
	|IDENTIFIER Initialiser
	;

Initialiser:
	|ASSIGN NUMBER
	;

/* End of Variable Statement */

/* IF statement */

IfStatement :
	
	|IFSYM  LPAREN IDENTIFIER RPAREN Statement ELSESYM Statement		{printf("\t \"If Statement\"\t");}
	|IFSYM  LPAREN IDENTIFIER RPAREN Statement
	|IFSYM LPAREN IDENTIFIER RPAREN LCURLY Statement RCURLY ELSESYM LCURLY Statement RCURLY
	;

/* End of IF statement */

/* SWITCH statement */

SwitchStatement:
	|SWITCHSYM LPAREN IDENTIFIER RPAREN caseBlock				{printf("\t \"Switch Statement\"\t");}
	;

caseBlock:
	| LCURLY CaseClauses RCURLY
	| LCURLY CaseClauses DefaultClause CaseClauses RCURLY
	;

CaseClauses: 
	|CaseClause
	|CaseClauses CaseClause
	;

CaseClause:
	|CASESYM IDENTIFIER COLON StatementList BREAKSYM SEMICOLON
	;

DefaultClause:
	|DEFAULTSYM COLON StatementList					{printf("\t \"Default Clause\"\t");}
	;

/* End of SWITCH statement */

/* Labelled Statement */

LabelledStatement :
	|IDENTIFIER COLON Statement						{printf("\t \"Labelled Statement\"\t");}
	;

/* End of Labelled Statement */

/* Throw Statement */

ThrowStatement:
	|THROWSYM IDENTIFIER SEMICOLON						{printf("\t \"Throw Statement\"\t");}
	;

/* End of Throw Statement */

/* Try Statement */

TryStatement :
	|TRYSYM StatementBlock Catch						{printf("\t \"Try Statement\"\t");}
	|TRYSYM StatementBlock Finally
	|TRYSYM StatementBlock Catch Finally
	;

Catch :
	|CATCHSYM LPAREN IDENTIFIER RPAREN StatementBlock			{printf("\t \"Catch Statement\"\t");}
	;

Finally :
	|FINALSYM StatementBlock						{printf("\t \"Final Block\"\t");}
	;

/* End of Try statement */


/* Debugger Statement */

DebuggerStatement:
	|DEBUGSYM SEMICOLON							{printf("\t \"Debugger Statement\"\t");}
	;

/* End of Debugger Statement */		
		
	
%%

main()
{
	yyparse();
	return 0;
}

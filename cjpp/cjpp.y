	/* Definition */

%{
	#include <stdio.h>
	//#include "ast/Node.h"
	int yyerror(char const *s);
	int yylex(void);
	
%}

%code requires { #include "ast/Node.h" }

%union {
	Expression* expr;
	Statement* stmt;
	Literal* l;
	Identifier* i;
}

%type <stmt> Statement SourceElement ExpressionStatement
%type <expr> Expression MemberExpression NewExpression BitwiseANDExpression BitwiseOrExpression PrimaryExpression LogicalAndExpression AssignmentExpression MultiplicativeExpression ShiftExpression UnaryExpression RelationalExpression LogicalOrExpression
BitwiseXORExpression ConditionalExpression AdditiveExpression EqualityExpression LeftHandSideExpression PostfixExpression 
%type <i> Identifier 
%type <l> Literal

%start Program

	/*  */
%token NUMBER HEXNUMBER IDENTIFIER FALSE TRUE UNKNOWN NULLLTOKEN

	/*  */
%token SEMICOLON COLON COMMA POINT QUESTION SINGLEQUOTE DOUBLEQUOTE BACKSLASH DOUBLE_STRING_LITERAL SINGLE_STRING_LITERAL

	/* Operators */
%left PLUS INC MINUS DEC MULTIPLY DIVIDE MOD

	/* Shift operators */
%left LSHIFT RSHIFT LRSHIFT

	/* Logic operatos */
%right NOT
%left OR AND

	/* Bitwise operators */
%left BITXOR BITOR BITAND
%right BITNOT

	/* Assignments */
%right ASSIGN ASSPLUS ASSMINUS ASSMULTIPLY ASSDIVIDE ASSMOD ASSBITXOR ASSBITOR ASSBITAND ASSLSHIFT ASSRSHIFT ASSLRSHIFT

	/* Comperators */
%left EQUAL IDENT NEQ NIDENT LSS GTR LEQ GEQ

	/* Brackets */
%token LPAREN RPAREN LBRACK RBRACK LCURLY RCURLY

	/* Keywords */
%token INSTANCEOF TYPEOF BREAK DO NEW VAR CASE ELSE RETURN VOID CATCH FINALLY CONTINUE FOR SWITCH WHILE THIS WITH DEBUGGER FUNCTION THROW DEFAULT IF TRY DELETE IN

%%

	

	/* 14 - Program */
Program: 
        SourceElements			
	;

SourceElements: 
        SourceElement 										
	| SourceElements SourceElement 									
	;

SourceElement: 
        Statement			{ $$ = $1; }
	;
	/* END 14 - Program */


	/* 12 - Statements */
Statement: 
	ExpressionStatement		{ $$ = $1; }		
	;


// 12.4 Expression Statement
ExpressionStatement: 
	Expression			{ $$ = new ExpressionStatement($1); }    
	;

	/* 11 - Expressions */
PrimaryExpression:
	Identifier			{ $$ = new PrimaryExpression($1); }
	| Literal			{ $$ = new PrimaryExpression($1); }
	;


// 11.2 Left-Hand-Side Expressions
MemberExpression: PrimaryExpression	{ $$ = $1; }
	;

NewExpression: MemberExpression		{ $$ = $1; }
	;

LeftHandSideExpression: NewExpression	{ $$ = $1; }
	;

// 11.3 Postfix Expressions
PostfixExpression: 
	LeftHandSideExpression		{ $$ = $1; }
	;

// 11.4 Unary Operators
UnaryExpression: 
	PostfixExpression		{ $$ = $1; }	
	;

// 11.5 Multiplicative Operators	
MultiplicativeExpression: 
	UnaryExpression			{ $$ = $1; }
	;

// 11.6 Additive Operators
AdditiveExpression: 
	MultiplicativeExpression	{ $$ = $1; }
	;

// 11.7 Bitwise Shift Operators
ShiftExpression: 
	AdditiveExpression		{ $$ = $1; }
	;

// 11.8 Relational Operators
RelationalExpression: 
	ShiftExpression			{ $$ = $1; }
	;

// 11.9 Equality Operators
EqualityExpression: 
	RelationalExpression		{ $$ = $1; }
	;

// 11.10 Binary Bitwise Operators
BitwiseANDExpression: 
	EqualityExpression		{ $$ = $1; }
	;

BitwiseXORExpression: 
	BitwiseANDExpression		{ $$ = $1; }
	;

BitwiseOrExpression: 
	BitwiseXORExpression		{ $$ = $1; }
	;

// 11.11 Binary Logical Operators
LogicalAndExpression: 
	BitwiseOrExpression		{ $$ = $1; }
	;

LogicalOrExpression: 
	LogicalAndExpression		{ $$ = $1; }
	;

// 11.12 Conditional Operator
ConditionalExpression: 
	LogicalOrExpression		{ $$ = $1; }
	;

// 11.13 Assignment Operators
AssignmentExpression: 
	ConditionalExpression					{ $$ = $1; }
	| LeftHandSideExpression ASSIGN AssignmentExpression	{ $$ = new AssignmentExpression($1, $3); }
	;

// 11.14 Comma Operator
Expression: 
	AssignmentExpression              { $$ = $1; }
	;

	/* END 11 - Expressions */

	/* 7.8 - Literals */
Literal: 
	NumericLiteral			  { $$ = new Literal(); }
	;

NumericLiteral: 
	DecimalLiteral
	| HexIntegerLiteral
	;

DecimalLiteral:
	NUMBER
	;

HexIntegerLiteral:
	HEXNUMBER
	;

Identifier:				
	IDENTIFIER			{ $$ = new Identifier((char *) "test"); }
	;
	/* END 7.6 Identifier Names and Identifiers */
%%



int yywrap(){
	return 1;
}
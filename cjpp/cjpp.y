	/* Definition */

%{
	#include <stdio.h>
	int yyerror(char const *s);
	int yylex(void);
	
%}

%code requires { #include "ast/Node.h" }
%locations

%union {
	Expression* expr;
	Statement* stmt;
	StatementList* stmtlist;
	Literal* l;
	Identifier* i;
	char* str;
	double num;
	int integer;
}

%type <stmtlist> Program SourceElements
%type <stmt> Statement SourceElement ExpressionStatement
%type <expr> Expression ExpressionNoIn MemberExpression NewExpression BitwiseANDExpression BitwiseOrExpression PrimaryExpression LogicalAndExpression   AssignmentExpression MultiplicativeExpression ShiftExpression UnaryExpression RelationalExpression LogicalOrExpression 
BitwiseXORExpression ConditionalExpression AdditiveExpression EqualityExpression LeftHandSideExpression PostfixExpression
BitwiseANDExpressionNoIn BitwiseOrExpressionNoIn LogicalAndExpressionNoIn AssignmentExpressionNoIn  RelationalExpressionNoIn LogicalOrExpressionNoIn BitwiseXORExpressionNoIn ConditionalExpressionNoIn EqualityExpressionNoIn
%type <i> Identifier 
%type <l> NumericLiteral Literal
%type <num> DecimalLiteral HexIntegerLiteral
%type <integer> AssignmentOperator

%start Program

	/*  */
%token <num> NUMBER HEXNUMBER
%token FALSE TRUE UNKNOWN NULLLTOKEN
%token <str> IDENTIFIER

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
        SourceElements			{ $$ = $1; $$->print(0); }
	;

SourceElements: 
        SourceElement 			{ $$ = new StatementList($1); } 							
	| SourceElements SourceElement 	{ $$ = $1; $$->append($2);    }								
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
	Expression SEMICOLON		{ $$ = new ExpressionStatement($1); }    
	;

	/* 11 - Expressions */
PrimaryExpression:
	Identifier			{ $$ = new PrimaryExpression($1); }
	| Literal			{ $$ = new PrimaryExpression($1); }
	| LPAREN Expression RPAREN      { $$ = $2; }
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
	UnaryExpression						{ $$ = $1; }
	| MultiplicativeExpression MULTIPLY UnaryExpression	{ $$ = new BinaryExpression($1, MULTIPLY, $3); }
	| MultiplicativeExpression DIVIDE UnaryExpression	{ $$ = new BinaryExpression($1, DIVIDE, $3); }
	| MultiplicativeExpression MOD UnaryExpression		{ $$ = new BinaryExpression($1, MOD, $3); }
	;

// 11.6 Additive Operators
AdditiveExpression: 
	MultiplicativeExpression				{ $$ = $1; }
	| AdditiveExpression PLUS MultiplicativeExpression	{ $$ = new BinaryExpression($1, PLUS, $3); }
	| AdditiveExpression MINUS MultiplicativeExpression	{ $$ = new BinaryExpression($1, MINUS, $3); }
	;

// 11.7 Bitwise Shift Operators
ShiftExpression: AdditiveExpression				{ $$ = $1; }
	| ShiftExpression LSHIFT AdditiveExpression		{ $$ = new BinaryExpression($1, LSHIFT, $3); }
	| ShiftExpression RSHIFT AdditiveExpression		{ $$ = new BinaryExpression($1, RSHIFT, $3); }
	| ShiftExpression LRSHIFT AdditiveExpression		{ $$ = new BinaryExpression($1, LRSHIFT, $3); }
	;

// 11.8 Relational Operators
RelationalExpression: 
	ShiftExpression						{ $$ = $1; }
	| RelationalExpression LSS ShiftExpression		{ $$ = new BinaryExpression($1, LSS, $3); }
	| RelationalExpression GTR ShiftExpression		{ $$ = new BinaryExpression($1, GTR, $3); }
	| RelationalExpression LEQ ShiftExpression		{ $$ = new BinaryExpression($1, LEQ, $3); }
	| RelationalExpression GEQ ShiftExpression		{ $$ = new BinaryExpression($1, GEQ, $3); }
	| RelationalExpression INSTANCEOF ShiftExpression	{ $$ = new BinaryExpression($1, INSTANCEOF, $3); }
	| RelationalExpression IN ShiftExpression		{ $$ = new BinaryExpression($1, IN, $3); }
	;

RelationalExpressionNoIn: 		
	ShiftExpression						{ $$ = $1; }
	| RelationalExpressionNoIn LSS ShiftExpression		{ $$ = new BinaryExpression($1, LSS, $3); }
	| RelationalExpressionNoIn GTR ShiftExpression		{ $$ = new BinaryExpression($1, GTR, $3); }
	| RelationalExpressionNoIn LEQ ShiftExpression		{ $$ = new BinaryExpression($1, LEQ, $3); }
	| RelationalExpressionNoIn GEQ ShiftExpression		{ $$ = new BinaryExpression($1, GEQ, $3); }
	| RelationalExpressionNoIn INSTANCEOF ShiftExpression	{ $$ = new BinaryExpression($1, INSTANCEOF, $3); }
	;

// 11.9 Equality Operators
EqualityExpression: 
	RelationalExpression					{ $$ = $1; }
	| EqualityExpression EQUAL RelationalExpression		{ $$ = new BinaryExpression($1, EQUAL, $3); }
	| EqualityExpression NEQ RelationalExpression		{ $$ = new BinaryExpression($1, NEQ, $3); }
	| EqualityExpression IDENT RelationalExpression		{ $$ = new BinaryExpression($1, IDENT, $3); }
	| EqualityExpression NIDENT RelationalExpression	{ $$ = new BinaryExpression($1, NIDENT, $3); }
	;

EqualityExpressionNoIn: RelationalExpressionNoIn		{ $$ = $1; }
	| EqualityExpressionNoIn EQUAL RelationalExpressionNoIn	{ $$ = new BinaryExpression($1, EQUAL, $3); }
	| EqualityExpressionNoIn NEQ RelationalExpressionNoIn	{ $$ = new BinaryExpression($1, NEQ, $3); }
	| EqualityExpressionNoIn IDENT RelationalExpressionNoIn	{ $$ = new BinaryExpression($1, IDENT, $3); }
	| EqualityExpressionNoIn NIDENT RelationalExpressionNoIn { $$ = new BinaryExpression($1, NIDENT, $3); }
	;

// 11.10 Binary Bitwise Operators
BitwiseANDExpression: 
	EqualityExpression					{ $$ = $1; }
	| BitwiseANDExpression BITAND EqualityExpression	{ $$ = new BinaryExpression($1, BITAND, $3); }
	;

BitwiseANDExpressionNoIn: 
	EqualityExpressionNoIn					{ $$ = $1; }
	| BitwiseANDExpressionNoIn BITAND EqualityExpressionNoIn { $$ = new BinaryExpression($1, BITAND, $3); }
	;

BitwiseXORExpression: 
	BitwiseANDExpression					{ $$ = $1; }
	| BitwiseXORExpression BITXOR BitwiseANDExpression	{ $$ = new BinaryExpression($1, BITXOR, $3); }
	;

BitwiseXORExpressionNoIn: 
	BitwiseANDExpressionNoIn				{ $$ = $1; }
	| BitwiseXORExpressionNoIn BITXOR BitwiseANDExpressionNoIn { $$ = new BinaryExpression($1, BITXOR, $3); }
	;

BitwiseOrExpression: 
	BitwiseXORExpression					{ $$ = $1; }
	| BitwiseOrExpression BITOR BitwiseXORExpression	{ $$ = new BinaryExpression($1, BITOR, $3); }
	;

BitwiseOrExpressionNoIn: 
	BitwiseXORExpressionNoIn				{ $$ = $1; }
	| BitwiseOrExpressionNoIn BITOR BitwiseXORExpressionNoIn { $$ = new BinaryExpression($1, BITOR, $3); }
	;

// 11.11 Binary Logical Operators
LogicalAndExpression: 
	BitwiseOrExpression					{ $$ = $1; }
	| LogicalAndExpression AND BitwiseOrExpression		{ $$ = new BinaryExpression($1, AND, $3); }
	;

LogicalAndExpressionNoIn: 
	BitwiseOrExpressionNoIn					{ $$ = $1; }
	| LogicalAndExpressionNoIn AND BitwiseOrExpressionNoIn	{ $$ = new BinaryExpression($1, AND, $3); }
	;

LogicalOrExpression: 
	LogicalAndExpression					{ $$ = $1; }
	| LogicalOrExpression OR LogicalAndExpression		{ $$ = new BinaryExpression($1, OR, $3); }
	;

LogicalOrExpressionNoIn: 
	LogicalAndExpressionNoIn				{ $$ = $1; }
	| LogicalOrExpressionNoIn OR LogicalAndExpressionNoIn	{ $$ = new BinaryExpression($1, OR, $3); }
	;

// 11.12 Conditional Operator
ConditionalExpression: 
	LogicalOrExpression					{ $$ = $1; }
	| LogicalOrExpression QUESTION AssignmentExpression COLON AssignmentExpression
	;

ConditionalExpressionNoIn: 
	LogicalOrExpressionNoIn					{ $$ = $1; }
	| LogicalOrExpressionNoIn QUESTION AssignmentExpression COLON AssignmentExpression
	;

// 11.13 Assignment Operators
AssignmentExpression: 
	ConditionalExpression 					{ $$ = $1; }
	| LeftHandSideExpression ASSIGN AssignmentExpression	{ $$ = new AssignmentExpression($1, $3); }
	| LeftHandSideExpression AssignmentOperator AssignmentExpression { $$ = new AssignmentExpression($1, $2, $3); }	
	;

AssignmentExpressionNoIn: 
	ConditionalExpressionNoIn			{ $$ = $1; }
	| LeftHandSideExpression ASSIGN AssignmentExpressionNoIn	{ $$ = new AssignmentExpression($1, $3); }
	| LeftHandSideExpression AssignmentOperator AssignmentExpressionNoIn { $$ = new AssignmentExpression($1, $2, $3); }
	;

AssignmentOperator: 
	ASSMULTIPLY 	{ $$ = ASSMULTIPLY; }
	| ASSDIVIDE 	{ $$ = ASSDIVIDE; }
	| ASSMOD 	{ $$ = ASSMOD; }
	| ASSPLUS 	{ $$ = ASSPLUS; }
	| ASSMINUS 	{ $$ = ASSMINUS; }
	| ASSLSHIFT 	{ $$ = ASSLSHIFT; }
	| ASSRSHIFT 	{ $$ = ASSRSHIFT ; }
	| ASSLRSHIFT 	{ $$ = ASSLRSHIFT; }
	| ASSBITAND 	{ $$ = ASSBITAND; }
	| ASSBITXOR 	{ $$ = ASSBITXOR; }
	| ASSBITOR	{ $$ = ASSBITOR; }
;

// 11.14 Comma Operator
Expression: 
	AssignmentExpression            { $$ = $1; }
	| Expression COMMA AssignmentExpression
	;

ExpressionNoIn: 
	AssignmentExpressionNoIn         { $$ = $1; }
	| ExpressionNoIn COMMA AssignmentExpressionNoIn
	;

	/* END 11 - Expressions */

	/* 7.8 - Literals */
Literal: 
	NumericLiteral			{ $$ = $1; }
	;

NumericLiteral: 
	DecimalLiteral			{ $$ = new NumericLiteral($1); }
	| HexIntegerLiteral		{ $$ = new NumericLiteral($1); }
	;

DecimalLiteral:
	NUMBER			        { $$ = $1; }
	;

HexIntegerLiteral:
	HEXNUMBER			{ $$ = $1; }
	;

Identifier:				
	IDENTIFIER			{ $$ = new Identifier($1); }
	;
	/* END 7.6 Identifier Names and Identifiers */
%%



int yywrap(){
	return 1;
}
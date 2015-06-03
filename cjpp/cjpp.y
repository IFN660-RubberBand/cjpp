	/* Definition */

%{
	#include <stdio.h>
	int yyerror(char const *s);
	int yylex(void);
	#include "ast/includefile.h"
	#include "ast/binaryexpression.h"
	
	Program* program;
%}

%code requires { #include "ast/includefile.h" }
%locations

%union {
	Expression* expr;
	Statement* stmt;
	FunctionDeclaration* funcdec;
	IdentifierList* identparmlist;
	StatementList* stmtlist;
	MemberExpression* memexpr;
	SourceElementList* sourceelementlist;
	VariableDec* vardec;
	Program* prog;
	VariableDecList* vardeclist;
	Literal* l;
	Identifier* i;
	char* str;
	double num;
	int integer;
	
}

%type <stmtlist> StatementList
%type <sourceelementlist> SourceElements FunctionBody
%type <vardec> VariableDeclaration VariableDeclarationNoIn
%type <vardeclist> VariableDeclarationList VariableDeclarationListNoIn
%type <memexpr> MemberExpression
%type <funcdec> FunctionDeclaration 
%type <identparmlist> FormalParameterList
%type <stmt> Statement SourceElement ExpressionStatement IterationStatement VariableStatement Block EmptyStatement IfStatement
%type <expr> Expression ExpressionNoIn NewExpression BitwiseANDExpression BitwiseOrExpression PrimaryExpression LogicalAndExpression   AssignmentExpression MultiplicativeExpression ShiftExpression UnaryExpression RelationalExpression LogicalOrExpression FunctionExpression
BitwiseXORExpression ConditionalExpression AdditiveExpression EqualityExpression LeftHandSideExpression PostfixExpression
BitwiseANDExpressionNoIn BitwiseOrExpressionNoIn LogicalAndExpressionNoIn AssignmentExpressionNoIn  RelationalExpressionNoIn LogicalOrExpressionNoIn BitwiseXORExpressionNoIn ConditionalExpressionNoIn EqualityExpressionNoIn Initialiser InitialiserNoIn CallExpression
%type <i> Identifier 
%type <l> NumericLiteral StringLiteral Literal BinaryLiteral ObjectLiteral
%type <num> DecimalLiteral HexIntegerLiteral
%type <integer> AssignmentOperator
%type <prog> Program

%start Program

	/*  */
%token <num> NUMBER HEXNUMBER
%token FALSE TRUE UNKNOWN NULLLTOKEN
%token <str> IDENTIFIER DOUBLE_STRING_LITERAL SINGLE_STRING_LITERAL

	/*  */
%token SEMICOLON COLON COMMA POINT QUESTION SINGLEQUOTE DOUBLEQUOTE BACKSLASH

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
%token TYPEOF BREAK DO NEW VAR CASE ELSE RETURN VOID CATCH FINALLY CONTINUE FOR SWITCH WHILE THIS WITH DEBUGGER FUNCTION THROW DEFAULT IF TRY DELETE INSTANCEOF
%left IN

%%

	

	/* 14 - Program */
Program: 
        SourceElements			{ program = new Program($1); program->print(); program->generateCode(); delete program; }
	;

SourceElements: 
    SourceElement 					{ $$ = new SourceElementList($1); } 							
	| SourceElements SourceElement 	{ $$ = $1; $$->append($2);    }								
	;

SourceElement: 
    Statement			{ $$ = $1; }
	|FunctionDeclaration		{ /*$$ = $1;*/ }
	;
	/* END 14 - Program */

	/* 13 - Function definition */
FunctionDeclaration: 
	FUNCTION Identifier LPAREN FormalParameterList RPAREN LCURLY FunctionBody RCURLY { $$ = new FunctionDeclaration($2, $4, $7); }
	| FUNCTION Identifier LPAREN RPAREN LCURLY FunctionBody RCURLY { $$ = new FunctionDeclaration($2, NULL, $6); }
	;

FunctionExpression: 
	FUNCTION Identifier LPAREN FormalParameterList RPAREN LCURLY FunctionBody RCURLY { $$ = new FunctionExpression($2, $4, $7); }
	| FUNCTION Identifier LPAREN RPAREN LCURLY FunctionBody RCURLY			{ $$ = new FunctionExpression($2,NULL, $6); }
	| FUNCTION LPAREN FormalParameterList RPAREN LCURLY FunctionBody RCURLY { $$ = new FunctionExpression(NULL, $3, $6); }
	| FUNCTION LPAREN RPAREN LCURLY FunctionBody RCURLY			{ $$ = new FunctionExpression(NULL, NULL, $5); }
	;

FormalParameterList: Identifier			{ $$ = new IdentifierList($1); }				
	| FormalParameterList Identifier	{ $$ = $1; $$->append($2);    }
	| FormalParameterList COMMA Identifier	{ $$ = $1; $$->append($3);    }
	;

FunctionBody: 
	SourceElements			{ $$ = $1; }
	|					{ $$ = NULL; }
	;
	/* END 13 - Function definition */

	/* 12 - Statements */
Statement: 
	ExpressionStatement		{ $$ = $1; }		
	| IterationStatement	{ $$ = $1; }
	| VariableStatement		{ $$ = $1; }
	| EmptyStatement        { $$ = $1; }
	| Block					{ $$ = $1; }
	| IfStatement 			{ $$ = $1; }
	;


EmptyStatement:
	SEMICOLON		{ $$ = new EmptyStatement(); }
	;
	
IfStatement:
	IF LPAREN Expression RPAREN Statement 				{ $$ = new IfStatement($3, $5, NULL); }
	| IF LPAREN Expression RPAREN Statement ELSE Statement 		{ $$ = new IfStatement($3, $5, $7); }
	;

Block: 
	LCURLY StatementList RCURLY 	{ $$ = new Block($2); }
	| LCURLY RCURLY 		{ $$ = new Block(NULL); }
;

StatementList: 
	Statement			{ $$ = new StatementList($1); } 
	| StatementList Statement	{ $$ = $1; $$->append($2);    }
;

// 12.2 Variable Statement
VariableStatement: 
	VAR VariableDeclarationList SEMICOLON			{ $$ = new VariableStatement($2); }
	;

VariableDeclarationList: 
	VariableDeclaration					{ $$ = new VariableDecList($1); }
	| VariableDeclarationList COMMA VariableDeclaration	{ $$ = $1; $$->append($3);    }
	;

VariableDeclarationListNoIn: 
	VariableDeclarationNoIn						{ $$ = new VariableDecList($1); }
	| VariableDeclarationListNoIn COMMA VariableDeclarationNoIn	{ $$ = $1; $$->append($3);    }
	;

VariableDeclaration: 
	Identifier Initialiser	{ $$ = new VariableDec($1, $2); }
	| Identifier		{ $$ = new VariableDec($1); }
	;

VariableDeclarationNoIn: 
	Identifier InitialiserNoIn	{ $$ = new VariableDec($1, $2); }
	| Identifier			{ $$ = new VariableDec($1); }
	;

Initialiser: 
	ASSIGN AssignmentExpression	{ $$ = $2; }
	;

InitialiserNoIn: 
	ASSIGN AssignmentExpressionNoIn	{ $$ = $2; }
	;


// 12.6 Iteration Statements
IterationStatement: 
	DO Statement WHILE LPAREN Expression RPAREN SEMICOLON 			{ $$ = new DoWhileIterationStatement($2, $5); }
	| WHILE LPAREN Expression RPAREN Statement				{ $$ = new WhileIterationStatement($3, $5); }
	| FOR LPAREN SEMICOLON SEMICOLON RPAREN Statement			{ $$ = new ForIterationStatement(NULL, NULL, NULL, $6); }
	| FOR LPAREN SEMICOLON SEMICOLON Expression RPAREN Statement		{ $$ = new ForIterationStatement(NULL, NULL, $5, $7); }
	| FOR LPAREN SEMICOLON Expression SEMICOLON RPAREN Statement		{ $$ = new ForIterationStatement(NULL, $4, NULL, $7); }
	| FOR LPAREN SEMICOLON Expression SEMICOLON Expression RPAREN Statement	{ $$ = new ForIterationStatement(NULL, $4, $6, $8); }
	| FOR LPAREN ExpressionNoIn SEMICOLON SEMICOLON RPAREN Statement			{ $$ = new ForIterationStatement($3, NULL, NULL, $7); }
	| FOR LPAREN ExpressionNoIn SEMICOLON SEMICOLON Expression RPAREN Statement		{ $$ = new ForIterationStatement($3, NULL, $6, $8); }
	| FOR LPAREN ExpressionNoIn SEMICOLON Expression SEMICOLON RPAREN Statement 		{ $$ = new ForIterationStatement($3, $5, NULL, $8); }
	| FOR LPAREN ExpressionNoIn SEMICOLON Expression SEMICOLON Expression RPAREN Statement 	{ $$ = new ForIterationStatement($3, $5, $7, $9); }
	| FOR LPAREN VAR VariableDeclarationListNoIn SEMICOLON SEMICOLON RPAREN Statement      	{ $$ = new ForVarIterationStatement($4, NULL, NULL, $8); }
	| FOR LPAREN VAR VariableDeclarationListNoIn SEMICOLON SEMICOLON Expression RPAREN Statement { $$ = new ForVarIterationStatement($4, NULL, $7, $9); }
	| FOR LPAREN VAR VariableDeclarationListNoIn SEMICOLON Expression SEMICOLON RPAREN Statement { $$ = new ForVarIterationStatement($4, $6, NULL, $9); }
	| FOR LPAREN VAR VariableDeclarationListNoIn SEMICOLON Expression SEMICOLON Expression RPAREN Statement { $$ = new ForVarIterationStatement($4, $6, $8, $10); }
	| FOR LPAREN LeftHandSideExpression IN Expression RPAREN Statement		{ $$ = new ForInIterationStatement($3, $5, $7); }
	| FOR LPAREN VAR VariableDeclarationNoIn IN Expression RPAREN Statement 	{ $$ = new ForVarInIterationStatement($4, $6, $8); }
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
MemberExpression: 
	PrimaryExpression	{ $$ = new MemberExpression($1); }
	| MemberExpression POINT Identifier { $$ = $1; $$->append($3); }
	;

NewExpression: 
	MemberExpression		{ $$ = $1; }
	;

LeftHandSideExpression: NewExpression	{ $$ = $1; }
	| CallExpression 					{ $$ = $1; }
	;

CallExpression: 
	MemberExpression LPAREN RPAREN 		{ $$ = new CallExpression($1, NULL); }
	;
	

// 11.3 Postfix Expressions
PostfixExpression: 
	LeftHandSideExpression		{ $$ = $1; }
	| LeftHandSideExpression INC	{ $$ = new PostfixExpression($1, INC); }
	| LeftHandSideExpression DEC	{ $$ = new PostfixExpression($1, DEC); }
	;

// 11.4 Unary Operators
UnaryExpression: 
	PostfixExpression		{ $$ = $1; }
	| DELETE UnaryExpression 	{ $$ = new UnaryExpression(DELETE, $2); }
	| VOID UnaryExpression 		{ $$ = new UnaryExpression(VOID, $2); }
	| TYPEOF UnaryExpression 	{ $$ = new UnaryExpression(TYPEOF, $2); }
	| INC UnaryExpression 		{ $$ = new UnaryExpression(INC, $2); }
	| DEC UnaryExpression 		{ $$ = new UnaryExpression(DEC, $2); }
	| PLUS UnaryExpression 		{ $$ = new UnaryExpression(PLUS, $2); }
	| MINUS UnaryExpression 	{ $$ = new UnaryExpression(MINUS, $2); }
	| BITNOT UnaryExpression 	{ $$ = new UnaryExpression(BITNOT, $2); }
	| NOT UnaryExpression 		{ $$ = new UnaryExpression(NOT, $2); }
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

EqualityExpressionNoIn: 
	RelationalExpressionNoIn				{ $$ = $1; }
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
	LogicalOrExpression									{ $$ = $1; }
	| LogicalOrExpression QUESTION AssignmentExpression COLON AssignmentExpression 		{ $$ = new TernaryExpression($1, $3, $5); }
	;

ConditionalExpressionNoIn: 
	LogicalOrExpressionNoIn									{ $$ = $1; }
	| LogicalOrExpressionNoIn QUESTION AssignmentExpression COLON AssignmentExpression	{ $$ = new TernaryExpression($1, $3, $5); }
	;

// 11.13 Assignment Operators
AssignmentExpression: 
	ConditionalExpression 							{ $$ = $1; }
	| LeftHandSideExpression ASSIGN AssignmentExpression			{ $$ = new AssignmentExpression($1, $3); }
	| LeftHandSideExpression AssignmentOperator AssignmentExpression 	{ $$ = new AssignmentExpression($1, $2, $3); }	
	;

AssignmentExpressionNoIn: 
	ConditionalExpressionNoIn						{ $$ = $1; }
	| LeftHandSideExpression ASSIGN AssignmentExpressionNoIn		{ $$ = new AssignmentExpression($1, $3); }
	| LeftHandSideExpression AssignmentOperator AssignmentExpressionNoIn 	{ $$ = new AssignmentExpression($1, $2, $3); }
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
	AssignmentExpression            	{ $$ = $1; }
	| Expression COMMA AssignmentExpression { $$ = $3; $$->prepend($1); }
	;

ExpressionNoIn: 
	AssignmentExpressionNoIn         		{ $$ = $1; }
	| ExpressionNoIn COMMA AssignmentExpressionNoIn { $$ = $3; $$->prepend($1); }
	;

	/* END 11 - Expressions */

	/* 7.8 - Literals */
Literal: 
	NumericLiteral			{ $$ = $1; }
	| StringLiteral 		{ $$ = $1; }
	| BinaryLiteral			{ $$ = $1; }
	| ObjectLiteral			{ $$ = $1; }
	;

ObjectLiteral:
	LCURLY RCURLY           { $$ = new ObjectLiteral(NULL);  }
	
BinaryLiteral:
	TRUE					{ $$ = new BooleanLiteral(true);  }
	| FALSE 				{ $$ = new BooleanLiteral(false); }

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

StringLiteral:
	DOUBLE_STRING_LITERAL 		{ $$ = new StringLiteral($1); }
	| SINGLE_STRING_LITERAL 	{ $$ = new StringLiteral($1); }
	;

Identifier:				
	IDENTIFIER			{ $$ = new Identifier($1); }
	;
	/* END 7.6 Identifier Names and Identifiers */
%%



int yywrap(){
	return 1;
}

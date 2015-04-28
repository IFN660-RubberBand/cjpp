	/* Definition */

%{
	#include <stdio.h>
	#include "ast/Node.h"
	#include "ast/iteration.h"
	int yyerror(char const *s);
	int yylex(void);
%}

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



%union {
	Expresssion* epxr;
	Statement* stmt;
	VariableDecList* vardeclist;
	VariableDec* vardeclist;
}

%type<expr> Expression ExpressionNoIn LeftHandSideExpression AssignmentExpression AssignmentExpressionNoIn Initialiser InitialiserNoIn
%type<stmt> IterationStatement
%type<vardeclist> VariableDeclarationList VariableDeclarationListNoIn
%type<vardec> VariableDeclaration VariableDeclarationNoIn

%%

	/* Rule */

	/* 14 - Program */
Program: SourceElements												//{ $$ = new SourceElement_node($1); }
	|
	;

SourceElements: SourceElement 										//{ $$ = new SourceElement_node($1); }
	| SourceElements SourceElement 									//{ $$ = new SourceElement_node($1, $2); }
	;

SourceElement: Statement
	| FunctionDeclaration
	;
	/* END 14 - Program */

	/* 13 - Function definition */
FunctionDeclaration: FUNCTION IDENTIFIER LPAREN FormalParameterList RPAREN LCURLY FunctionBody RCURLY
	| FUNCTION IDENTIFIER LPAREN RPAREN LCURLY FunctionBody RCURLY
	;

FunctionExpression: FunctionDeclaration
	| FUNCTION LPAREN FormalParameterList RPAREN LCURLY FunctionBody RCURLY
	| FUNCTION LPAREN RPAREN LCURLY FunctionBody RCURLY
	;

FormalParameterList: IDENTIFIER
	| FormalParameterList IDENTIFIER
	;

FunctionBody: SourceElements
	|
	;
	/* END 13 - Function definition */

	/* 12 - Stetements */
Statement: Block
	| VariableStatement
	| EmptyStatement
	//| ExpressionStatement
	| IfStatement
	| IterationStatement
	| ContinueStatement
	| BreakStatement
	| ReturnStatement
	| WithStatement
	| LabelledStatement
	| SwitchStatement
	| ThrowStatement
	| TryStatement
	| DebuggerStatement
	;

// 12.1 Block
Block: LCURLY StatementList RCURLY										//{ $$ = $2; }
	| LCURLY RCURLY																			//{ $$ = new Block(); }
	;

StatementList: Statement
	| StatementList Statement
	;

// 12.2 Variable Statement
VariableStatement: VAR VariableDeclarationList SEMICOLON 				{printf("\t \"Variable Statement\"\t");}
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


// 12.3 Empty Statement
EmptyStatement: 																//{ $$ = new NEmptyStatement(); }
	;

// 12.4 Expression Statement
// todo
//ExpressionStatement: 
//	;

// 12.5 if Statement
IfStatement: IF LPAREN Expression RPAREN Statement ELSE Statement 				//{ $$ = new NIfStatement($3, $5, $6); }
	| IF LPAREN Expression RPAREN Statement 									//{ $$ = new NIfStatement($3, $5, null); }
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

// 12.7 continue Statement
ContinueStatement: CONTINUE SEMICOLON
	| CONTINUE IDENTIFIER SEMICOLON
	;

// 12.8 The break Statement
BreakStatement: BREAK SEMICOLON
	| BREAK IDENTIFIER SEMICOLON
	;

// 12.9 The return Statement
ReturnStatement: RETURN SEMICOLON
	| RETURN Expression SEMICOLON
	;

// 12.10 The with Statement
WithStatement: WITH LPAREN Expression RPAREN Statement
	;

// 12.11 The switch Statement
SwitchStatement: SWITCH LPAREN Expression RPAREN CaseBlock
	;

CaseBlock: LCURLY CaseClauses RCURLY
	| LCURLY RCURLY
	| LCURLY CaseClause DefaultClause CaseClause RCURLY
	| LCURLY DefaultClause CaseClause RCURLY
	| LCURLY CaseClause DefaultClause RCURLY
	| LCURLY DefaultClause RCURLY
	;

CaseClause: CASE Expression COLON StatementListOpt
	;

CaseClauses: CaseClause
	| CaseClauses CaseClause
	;

DefaultClause: DEFAULT COLON StatementListOpt
	;

StatementListOpt: 
	| StatementList
	;

// 12.12 Labelled Statement
LabelledStatement: IDENTIFIER COLON Statement 									//{ $$ = new NLabelledStatement($1, $3); }
	;

// 12.13 The throw Statement
ThrowStatement: THROW Expression SEMICOLON
	;

// 12.14 The try Statement
Finally: FINALLY Block
	;

Catch: CATCH LPAREN IDENTIFIER RPAREN Block
	;

TryStatement: TRY Block Catch
	| TRY Block Finally
	| TRY Block CATCH Finally
	;

// 12.15 The debugger Statement
DebuggerStatement: DEBUGGER SEMICOLON 											//{ $$ = new NDebuggerStatement($1); }
	;
	/* END 12 - Stetements */

	/* 11 - Expressions */
PrimaryExpression: THIS
	| IDENTIFIER
	| Literal
	| ArrayLiteral
	| ObjectLiteral
	| LPAREN Expression RPAREN
	;
// 11.1.4 Array Initialiser
ArrayLiteral: LBRACK Elison RBRACK
	| LBRACK RBRACK
	| LBRACK ElementList RBRACK
	| LBRACK ElementList COMMA Elison RBRACK
	| LBRACK ElementList COMMA RBRACK
	;

ElementList: Elison AssignmentExpression
	| AssignmentExpression
	| ElementList COMMA Elison AssignmentExpression
	| ElementList AssignmentExpression
	;

Elison: COMMA
	| Elison COMMA
	;

// 11.1.5 Object Initialiser
ObjectLiteral: LCURLY RCURLY
	| LCURLY PropertyNameAndValueList RCURLY
	| LCURLY PropertyNameAndValueList COMMA RCURLY
	;

PropertyNameAndValueList: PropertyAssignment
	| PropertyNameAndValueList COMMA PropertyAssignment
	;

PropertyAssignment: PropertyName COLON AssignmentExpression
	| IDENTIFIER PropertyName LPAREN RPAREN LCURLY FunctionBody RCURLY
	| IDENTIFIER PropertyName LPAREN PropertySetParameterList RPAREN LCURLY FunctionBody RCURLY
	;

PropertyName: IdentifierName
	| StringLiteral
	| NumericLiteral
	;

PropertySetParameterList: IDENTIFIER
	;

// 11.2 Left-Hand-Side Expressions
MemberExpression: PrimaryExpression
	| FunctionExpression
	| MemberExpression LBRACK Expression RBRACK
	| MemberExpression POINT IdentifierName
	| NEW MemberExpression Arguments
	;

NewExpression: MemberExpression
	| NEW NewExpression
	;

CallExpression: MemberExpression Arguments
	| CallExpression Arguments
	| CallExpression LBRACK Expression RBRACK
	| CallExpression POINT IdentifierName
	;

Arguments: LPAREN RPAREN
	| LPAREN ArgumentList RPAREN
	;

ArgumentList: AssignmentExpression
	| ArgumentList COMMA AssignmentExpression
	;

LeftHandSideExpression: NewExpression
	| CallExpression
	;

// 11.3 Postfix Expressions
PostfixExpression: LeftHandSideExpression
	| LeftHandSideExpression INC
	| LeftHandSideExpression DEC
	;

// 11.4 Unary Operators
UnaryExpression: PostfixExpression										//{ $$ = new PostfixExpression_node($1); }
	| DELETE UnaryExpression											//{ $$ = new UnaryExpression_node($2); }
	| VOID UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	| TYPEOF UnaryExpression											//{ $$ = new UnaryExpression_node($2); }
	| INC UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	| DEC UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	| PLUS UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	| MINUS UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	| BITNOT UnaryExpression											//{ $$ = new UnaryExpression_node($2); }
	| NOT UnaryExpression												//{ $$ = new UnaryExpression_node($2); }
	;

// 11.5 Multiplicative Operators
MultiplicativeExpression: UnaryExpression
	| MultiplicativeExpression MULTIPLY UnaryExpression
	| MultiplicativeExpression DIVIDE UnaryExpression
	| MultiplicativeExpression MOD UnaryExpression
	;

// 11.6 Additive Operators
AdditiveExpression: MultiplicativeExpression
	| AdditiveExpression PLUS MultiplicativeExpression
	| AdditiveExpression MINUS MultiplicativeExpression
	;

// 11.7 Bitwise Shift Operators
ShiftExpression: AdditiveExpression
	| ShiftExpression LSHIFT AdditiveExpression
	| ShiftExpression RSHIFT AdditiveExpression
	| ShiftExpression LRSHIFT AdditiveExpression
	;

// 11.8 Relational Operators
RelationalExpression: ShiftExpression
	| RelationalExpression LSS ShiftExpression
	| RelationalExpression GTR ShiftExpression
	| RelationalExpression LEQ ShiftExpression
	| RelationalExpression GEQ ShiftExpression
	| RelationalExpression INSTANCEOF ShiftExpression
	| RelationalExpression IN ShiftExpression
	;

RelationalExpressionNoIn: ShiftExpression
	| RelationalExpressionNoIn LSS ShiftExpression
	| RelationalExpressionNoIn GTR ShiftExpression
	| RelationalExpressionNoIn LEQ ShiftExpression
	| RelationalExpressionNoIn GEQ ShiftExpression
	| RelationalExpressionNoIn INSTANCEOF ShiftExpression
	| RelationalExpressionNoIn IN ShiftExpression
	;

// 11.9 Equality Operators
EqualityExpression: RelationalExpression
	| EqualityExpression EQUAL RelationalExpression
	| EqualityExpression NEQ RelationalExpression
	| EqualityExpression IDENT RelationalExpression
	| EqualityExpression NIDENT RelationalExpression
	;

EqualityExpressionNoIn: RelationalExpressionNoIn
	| EqualityExpressionNoIn EQUAL RelationalExpressionNoIn
	| EqualityExpressionNoIn NEQ RelationalExpressionNoIn
	| EqualityExpressionNoIn IDENT RelationalExpressionNoIn
	| EqualityExpressionNoIn NIDENT RelationalExpressionNoIn
	;

// 11.10 Binary Bitwise Operators
BitwiseANDExpression: EqualityExpression
	| BitwiseANDExpression BITAND EqualityExpression
	;

BitwiseANDExpressionNoIn: EqualityExpressionNoIn
	| BitwiseANDExpressionNoIn BITAND EqualityExpressionNoIn
	;

BitwiseXORExpression: BitwiseANDExpression
	| BitwiseXORExpression BITXOR BitwiseANDExpression
	;

BitwiseXORExpressionNoIn: BitwiseANDExpressionNoIn
	| BitwiseXORExpressionNoIn BITXOR BitwiseANDExpressionNoIn
	;

BitwiseOrExpression: BitwiseXORExpression
	| BitwiseOrExpression BITOR BitwiseXORExpression
	;

BitwiseOrExpressionNoIn: BitwiseXORExpressionNoIn
	| BitwiseOrExpressionNoIn BITOR BitwiseXORExpressionNoIn
	;

// 11.11 Binary Logical Operators
LogicalAndExpression: BitwiseOrExpression
	| LogicalAndExpression AND BitwiseOrExpression
	;

LogicalAndExpressionNoIn: BitwiseOrExpressionNoIn
	| LogicalAndExpressionNoIn AND BitwiseOrExpressionNoIn
	;

LogicalOrExpression: LogicalAndExpression
	| LogicalOrExpression OR LogicalAndExpression
	;

LogicalOrExpressionNoIn: LogicalAndExpressionNoIn
	| LogicalOrExpressionNoIn OR LogicalAndExpressionNoIn
	;

// 11.12 Conditional Operator
ConditionalExpression: LogicalOrExpression
	| LogicalOrExpression QUESTION AssignmentExpression COLON AssignmentExpression
	;

ConditionalExpressionNoIn: LogicalOrExpressionNoIn
	| LogicalOrExpressionNoIn QUESTION AssignmentExpression COLON AssignmentExpression
	;

// 11.13 Assignment Operators
AssignmentExpression: ConditionalExpression 
	| LeftHandSideExpression ASSIGN AssignmentExpression
	| LeftHandSideExpression AssignmentOperator AssignmentExpression
	;

AssignmentExpressionNoIn: ConditionalExpressionNoIn
	| LeftHandSideExpression ASSIGN AssignmentExpressionNoIn
	| LeftHandSideExpression AssignmentOperator AssignmentExpressionNoIn
	;

AssignmentOperator: ASSMULTIPLY ASSDIVIDE ASSMOD ASSPLUS ASSMINUS ASSLSHIFT ASSRSHIFT ASSLRSHIFT ASSBITAND ASSBITXOR ASSBITOR
	;

// 11.14 Comma Operator
Expression: AssignmentExpression
	| Expression COMMA AssignmentExpression
	;

ExpressionNoIn: AssignmentExpressionNoIn
	| ExpressionNoIn COMMA AssignmentExpressionNoIn
	;
	/* END 11 - Expressions */

	/* 7.8 - Literals */
Literal: NullLiteral 
	| BooleanLiteral
	| NumericLiteral
	| StringLiteral
	| RegularExpressionLiteral
	;

NullLiteral: NULLLTOKEN
	;

BooleanLiteral: TRUE
	| FALSE
	;

NumericLiteral: DecimalLiteral
	| HexIntegerLiteral
	;

DecimalLiteral:
	NUMBER
	;

HexIntegerLiteral:
	HEXNUMBER
	;

Identifier:
	IDENTIFIER
	;

// todo
StringLiteral: DOUBLE_STRING_LITERAL
	| SINGLE_STRING_LITERAL
	;

// todo
RegularExpressionLiteral:
	;
	/* END 7.8 - Literals */

	/* 7.6 Identifier Names and Identifiers */
	// todo
	IdentifierName:
	;
	/* END 7.6 Identifier Names and Identifiers */
%%

	/* Subroutine */

int yywrap(){
	return 1;
}

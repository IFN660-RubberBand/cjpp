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


%%
program:   
      Statement program		
   	|
   	;

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

/* End of Statment Block */

/* Empty Statement */

EmptyStatement:
	|SEMICOLON		        					{printf("\t \"Empty Statement\"\t");}
	;	

/* End of Empty Statement */

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

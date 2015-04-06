	/* Definition */

%{ 	/* C */
	#include "cjpp.tab.h"

	void yyerror(char const *);
	int yyparse(void);

	int line = 1;
	int column = 1;
%} 	/* END C */

%option yylineno

letter 		([a-zA-Z])

hexdigit 	([0-9a-fA-F])
hexnumber 	0x{hexdigit}+

digit 		([0-9])
num1 		([-+]?{digit}+\.?([eE][-+]?{digit}+)?)
num2 		([-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?)
number 		{num1}|{num2}

identifier 	(^[_$a-zA-Z][_$a-zA-Z0-9]*$)

%%

	/* Rule */

[ \t]

[\n] 				{ yylineno++; fprintf(yyout, "\n");}

{number} 			{ fprintf(yyout, " NUMBER(%f)", strtod( yytext , NULL )); 					return NUMBER; }
{hexnumber} 		{ fprintf(yyout, " HEXNUMBER(%f)", (double) strtol(yytext+2, NULL, 16)); 	return HEXNUMBER; }

";" 				{ fprintf(yyout, " SEMICOLON"); 	return SEMICOLON; }
":" 				{ fprintf(yyout, " COLON"); 		return COLON; }
"," 				{ fprintf(yyout, " COMMA"); 		return COMMA; }
"." 				{ fprintf(yyout, " POINT"); 		return POINT; }
"?" 				{ fprintf(yyout, " QUESTION"); 		return QUESTION; }

	/* operators */
"\+" 				{ fprintf(yyout, " PLUS"); 			return PLUS; }
"\+\+" 				{ fprintf(yyout, " INC"); 			return INC; }
"-" 				{ fprintf(yyout, " MINUS"); 		return MINUS; }
"--" 				{ fprintf(yyout, " DEC"); 			return DEC; }
"\*" 				{ fprintf(yyout, " MULTIPLY"); 		return MULTIPLY; }
"\/" 				{ fprintf(yyout, " DIVIDE"); 		return DIVIDE; }
"%" 				{ fprintf(yyout, " MOD"); 			return MOD; }
 
 	/* all assignments */ 
"=" 				{ fprintf(yyout, " ASSIGN"); 		return ASSIGN; }
"\+=" 				{ fprintf(yyout, " ASSPLUS"); 		return ASSPLUS; }
"-=" 				{ fprintf(yyout, " ASSMINUS"); 		return ASSMINUS; }
"\*=" 				{ fprintf(yyout, " ASSMULTIPLY"); 	return ASSMULTIPLY; }
"\/=" 				{ fprintf(yyout, " ASSDIVIDE"); 	return ASSDIVIDE; }
"%=" 				{ fprintf(yyout, " ASSMOD"); 		return ASSMOD; }
"^=" 				{ fprintf(yyout, " ASSBITXOR"); 	return ASSBITXOR; }
"|=" 				{ fprintf(yyout, " ASSBITOR"); 		return ASSBITOR; }
"&=" 				{ fprintf(yyout, " ASSBITAND"); 	return ASSBITAND; }
"<<=" 				{ fprintf(yyout, " ASSLSHIFT"); 	return ASSLSHIFT; }
">>=" 				{ fprintf(yyout, " ASSRSHIFT"); 	return ASSRSHIFT; }
">>>=" 				{ fprintf(yyout, " ASSLRSHIFT"); 	return ASSLRSHIFT; }

 	/* comperator */
"==" 				{ fprintf(yyout, " EQUAL"); 		return EQUAL; }
"===" 				{ fprintf(yyout, " IDENT"); 		return IDENT; }
"!=" 				{ fprintf(yyout, " NEQ"); 			return NEQ; }
"!==" 				{ fprintf(yyout, " NIDENT"); 		return NIDENT; }
"<" 				{ fprintf(yyout, " LSS"); 			return LSS; }
">" 				{ fprintf(yyout, " GTR"); 			return GTR; }
"<=" 				{ fprintf(yyout, " LEQ"); 			return LEQ; }
">=" 				{ fprintf(yyout, " GEQ"); 			return GEQ; }

 	/* shift operation */
"<<" 				{ fprintf(yyout, " LSHIFT"); 		return LSHIFT; }
">>" 				{ fprintf(yyout, " RSHIFT"); 		return RSHIFT; }
">>>" 				{ fprintf(yyout, " LRSHIFT"); 		return LRSHIFT; }

 	/* logic operator */ 
"!" 				{ fprintf(yyout, " NOT"); 			return NOT; }
"||" 				{ fprintf(yyout, " OR"); 			return OR; }
"&&" 				{ fprintf(yyout, " AND"); 			return AND; }

 	/* bitwise operator */ 
"^" 				{ fprintf(yyout, " BITXOR"); 		return BITXOR; }
"|" 				{ fprintf(yyout, " BITOR"); 		return BITOR; }
"&" 				{ fprintf(yyout, " BITAND"); 		return BITAND; }
"~" 				{ fprintf(yyout, " BITNOT"); 		return BITNOT; }

 	/* boolean constants */
"false" 			{ fprintf(yyout, " FALSE"); 		return FALSE; }
"true" 				{ fprintf(yyout, " TRUE"); 			return TRUE; }

 	/* null literal */
"null" 				{ fprintf(yyout, " NULLLTOKEN"); 	return NULLLTOKEN; }

	/* Brackets */
"(" 				{ fprintf(yyout, " LPAREN"); 		return LPAREN; }
")" 				{ fprintf(yyout, " RPAREN"); 		return RPAREN; }
"[" 				{ fprintf(yyout, " LBRACK"); 		return LBRACK; }
"]" 				{ fprintf(yyout, " RBRACK"); 		return RBRACK; }
"{" 				{ fprintf(yyout, " LCURLY"); 		return LCURLY; }
"}" 				{ fprintf(yyout, " RCURLY"); 		return RCURLY; }

	/* ReservedWord */
"instanceof" 		{ fprintf(yyout, " INSTANCEOF"); 	return INSTANCEOF; }
"typeof" 			{ fprintf(yyout, " TYPEOF"); 		return TYPEOF; }
"break" 			{ fprintf(yyout, " BREAK"); 		return BREAK; }
"do" 				{ fprintf(yyout, " DO"); 			return DO; }
"new" 				{ fprintf(yyout, " NEW"); 			return NEW; }
"var" 				{ fprintf(yyout, " VAR"); 			return VAR; }
"case" 				{ fprintf(yyout, " CASE"); 			return CASE; }
"else" 				{ fprintf(yyout, " ELSE"); 			return ELSE; }
"return" 			{ fprintf(yyout, " RETURN"); 		return RETURN; }
"void" 				{ fprintf(yyout, " VOID"); 			return VOID; }
"catch" 			{ fprintf(yyout, " CATCH"); 		return CATCH; }
"finally" 			{ fprintf(yyout, " FINALLY"); 		return FINALLY; }
"continue" 			{ fprintf(yyout, " CONTINUE"); 		return CONTINUE; }
"for" 				{ fprintf(yyout, " FOR"); 			return FOR; }
"switch" 			{ fprintf(yyout, " SWITCH"); 		return SWITCH; }
"while" 			{ fprintf(yyout, " WHILE"); 		return WHILE; }
"this" 				{ fprintf(yyout, " THIS"); 			return THIS; }
"with" 				{ fprintf(yyout, " WITH"); 			return WITH; }
"debugger" 			{ fprintf(yyout, " DEBUGGER"); 		return DEBUGGER; }
"function" 			{ fprintf(yyout, " FUNCTION"); 		return FUNCTION; }
"throw" 			{ fprintf(yyout, " THROW"); 		return THROW; }
"default" 			{ fprintf(yyout, " DEFAULT"); 		return DEFAULT; }
"if" 				{ fprintf(yyout, " IF"); 			return IF; }
"try" 				{ fprintf(yyout, " TRY"); 			return TRY; }
"delete" 			{ fprintf(yyout, " DELETE"); 		return DELETE; }
"in" 				{ fprintf(yyout, " IN"); 			return IN; }

	/* Identifier */
{identifier} 		{ fprintf(yyout, " IDENTIFIER"); 	return IDENTIFIER; }

%%

	/* Subroutine */

extern int yyparse();

/* error handling */
void yyerror(char const *s){
	printf("%d:%d\n%s", line, column, s);
}

/* wraping related files */
int yywrap(void) {
	return 1;
}

int main(void) {
	yyparse();
	yylex();

	printf("\t%d\t%d\n", line, column);

	yylex_destroy();
}

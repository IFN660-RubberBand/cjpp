%option noyywrap

%{
	#include "stdio.h"
	#include <string.h>
	#include "parser.tab.h"

	int mylineno = 1;
	void yyerror(char *message)
	{
		printf("Error: %s\n",message);
	}
%}

%x STRING1
%x STRING2

digit 		[0-9]
hexdigit 	[0-9a-fA-F]
letter 		[a-zA-Z]
name 		({letter}|{digit}|\$)({letter}|{digit}|[_.\-/$])*

hexnumber 	0x{hexdigit}+
num1 		[-+]?{digit}+\.?([eE][-+]?{digit}+)?
num2 		[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
number 		{num1}|{num2}

%%

	/* whitespace */
[\t ]
[\n\r] {
	++mylineno;
	fprintf(yyout, "\n");
}

	/* comments */
"/*" {
	int c;
	while((c = yyinput()) != 0) {
		if(c == '\n')
			++mylineno;
		else if(c == '*') {
			if((c = yyinput()) == '/')
				break;
			else
				unput(c);
		}
	}
}

"//" {
	int c;
	++mylineno;
	while((c = yyinput()) != 0) {
		if(c == '\n')
			break;
	}
}

	/* String - looks stupid, but works*/
\"   BEGIN(STRING1);

<STRING1>[^\\\n"]* 		yymore();
<STRING1><<EOF>> 		yyerror("EOF in string."); BEGIN(INITIAL);
<STRING1>\n 			fprintf(yyout, "unterminated string line %d", mylineno); BEGIN(INITIAL);
<STRING1>\\[\\nt"\n] 	yymore();
<STRING1>\\ 			fprintf(yyout, "incorrect escaped character in line %d", mylineno); yyterminate();
<STRING1>\" 		{
						yytext[yyleng-1] = '\0';
						fprintf(yyout, " STRING(%s)", yytext, yyleng); BEGIN(INITIAL);
					}

\'   BEGIN(STRING2);

<STRING2>[^\\\n']* 		yymore();
<STRING2><<EOF>> 		yyerror("EOF in string."); BEGIN(INITIAL);
<STRING2>\n 			fprintf(yyout, "unterminated string line %d", mylineno); BEGIN(INITIAL);
<STRING2>\\[\\nt'\n] 	yymore();
<STRING2>\\ 			fprintf(yyout, "incorrect escaped character in line %d", mylineno); yyterminate();
<STRING2>\' 		{
						yytext[yyleng-1] = '\0';
						fprintf(yyout, " STRING(%s)", yytext, yyleng); BEGIN(INITIAL);
					}

{number} 				fprintf(yyout, " NUMBER(%f)", strtod( yytext , NULL ));					return NUMBER;
{hexnumber} 			fprintf(yyout, " HEXNUMBER(%f)", (double) strtol(yytext+2, NULL, 16)); 	return HEXNUMBER;

";" 				fprintf(yyout, " SEMICOLON"); 		return SEMICOLON;
":" 				fprintf(yyout, " COLON"); 			return COLON;
"," 				fprintf(yyout, " COMMA"); 			return COMMA;
"." 				fprintf(yyout, " POINT"); 			return POINT;
"?" 				fprintf(yyout, " QUESTION"); 		return QUESTION;

	/* operators */
"\+"				fprintf(yyout, " PLUS");			return PLUS;
"\+\+"				fprintf(yyout, " INC");				return INC;
"-"					fprintf(yyout, " MINUS");			return MINUS;
"--"			 	fprintf(yyout, " DEC");				return DEC;
"\*"				fprintf(yyout, " MULTIPLY");	 	return MULTIPLY;
"\/"				fprintf(yyout, " DIVIDE");			return DIVIDE;
"%"					fprintf(yyout, " MOD");				return MOD;
 
 	/* all assignments */ 
"="					fprintf(yyout, " ASSIGN");			return ASSIGN;
"\+="				fprintf(yyout, " ASSPLUS");			return ASSPLUS;
"-="				fprintf(yyout, " ASSMINUS");		return ASSMINUS;
"\*="				fprintf(yyout, " ASSMULTIPLY");	 	return ASSMULTIPLY;
"\/="				fprintf(yyout, " ASSDIVIDE");		return ASSDIVIDE;
"%="				fprintf(yyout, " ASSMOD");			return ASSMOD;
"^="				fprintf(yyout, " ASSBITXOR");		return ASSBITXOR;
"|="				fprintf(yyout, " ASSBITOR");		return ASSBITOR;
"&="				fprintf(yyout, " ASSBITAND");		return ASSBITAND;
"<<="				fprintf(yyout, " ASSLSHIFT");		return ASSLSHIFT;
">>="				fprintf(yyout, " ASSRSHIFT");		return ASSRSHIFT;
">>>="				fprintf(yyout, " ASSLRSHIFT");		return ASSLRSHIFT;

 	/* comperator */
"=="				fprintf(yyout, " EQUAL");
"==="				fprintf(yyout, " IDENT");
"!="				fprintf(yyout, " NEQ");
"!=="				fprintf(yyout, " NIDENT");
"<"					fprintf(yyout, " LSS");
">"					fprintf(yyout, " GTR");
"<="				fprintf(yyout, " LEQ");
">="				fprintf(yyout, " GEQ");

 	/* shift operation */
"<<"				fprintf(yyout, " LSHIFT");		return LSHIFT;
">>"				fprintf(yyout, " RSHIFT");		return RSHIFT;
">>>"				fprintf(yyout, " LRSHIFT");		return LRSHIFT;

 	/* logic operator */ 
"!"					fprintf(yyout, " NOT");			return NOT;
"||"				fprintf(yyout, " OR");			return OR;
"&&"				fprintf(yyout, " AND");			return AND;

 	/* bitwise operator */ 
"^"					fprintf(yyout, " BITXOR");		return BITXOR;
"|"					fprintf(yyout, " BITOR");		return BITOR;
"&"					fprintf(yyout, " BITAND");		return BITAND;
"~"					fprintf(yyout, " BITNOT");		return BITNOT;

 	/* boolean constants */
"false"				fprintf(yyout, " FALSE");
"true"				fprintf(yyout, " TRUE");
	
 	/* null literal */
"null"				fprintf(yyout, " NULL");
		
 	/* brackets */
"("					fprintf(yyout, " LPAREN"); 			return LPAREN;
")"					fprintf(yyout, " RPAREN"); 		 	return RPAREN;
"["					fprintf(yyout, " LBRACK"); 		 	return LBRACK;
"]"					fprintf(yyout, " RBRACK"); 		 	return RBRACK;
"{"					fprintf(yyout, " LCURLY"); 		 	return LCURLY;
"}"					fprintf(yyout, " RCURLY"); 		 	return RCURLY;
		

 	/* keywords */
"break"				fprintf(yyout, " BREAKSYM"); 	
"case"				fprintf(yyout, " CASESYM");		 
"catch"				fprintf(yyout, " CATCHSYM");	 
"continue"			fprintf(yyout, " CONTSYM");		 
"debugger"			fprintf(yyout, " DEBUGSYM");	 
"default"			fprintf(yyout, " DEFAULTSYM");	
"delete"			fprintf(yyout, " DELSYM");		 
"do"				fprintf(yyout, " DOSYM");		 
"else"				fprintf(yyout, " ELSESYM");		
"finally"			fprintf(yyout, " FINALSYM");	 
"for"				fprintf(yyout, " FORSYM");		 
"function"			fprintf(yyout, " FUNCSYM");		 
"if"				fprintf(yyout, " IFSYM");		 
"in"				fprintf(yyout, " INSYM");		 
"instanceof"		fprintf(yyout, " INSTSYM");		 
"new"				fprintf(yyout, " NEWSYM");		 
"return"			fprintf(yyout, " RETURNSYM");	 
"switch"			fprintf(yyout, " SWITCHSYM");	 
"this"				fprintf(yyout, " THISSYM");		 
"throw"				fprintf(yyout, " THROWSYM");	 
"try"				fprintf(yyout, " TRYSYM");		 
"typeof"			fprintf(yyout, " TYPEOFSYM");	 
"var"				fprintf(yyout, " VARSYM");			return VARSYM; 
"void"				fprintf(yyout, " VOIDSYM");		 
"while"				fprintf(yyout, " WHILESYM");	 	return WHILESYM;
"with"				fprintf(yyout, " WITHSYM");		 
		
 	/* future reserved keywords */
"class"				yyerror("Usage of reserved keyword 'class'");
"enum"				yyerror("Usage of reserved keyword 'enum'");
"extends"			yyerror("Usage of reserved keyword 'extends'");
"super"				yyerror("Usage of reserved keyword 'super'");
"const"				yyerror("Usage of reserved keyword 'const'");
"export"			yyerror("Usage of reserved keyword 'export'");
"import" 			yyerror("Usage of reserved keyword 'import'");
		
					
 	/* indentifiers */
{name}				fprintf(yyout, " IDENTIFIER(%s)", yytext);		return IDENTIFIER;

 	/* Unknown */
. 					fprintf(yyout, " unknown identifier %s in line %d", yytext, mylineno); yyterminate();

%%

void asdasd()
{
	yyout=fopen("outtest.txt", "w");
	yylex();
	fclose(yyout);
}
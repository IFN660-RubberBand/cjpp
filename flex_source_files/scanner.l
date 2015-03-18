%option noyywrap

%{
	#include "stdio.h"
	int mylineno = 1;
%}

digit	[0-9]
letter	[a-zA-Z]
name	({letter}|{digit}|\$)({letter}|{digit}|[_.\-/$])*
num1	[-+]?{digit}+\.?([eE][-+]?{digit}+)?
num2	[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
number	{num1}|{num2}

%%
			/* whitespace */
[\t]
" "
[\n\r]				{ ++mylineno;
					  fprintf(yyout, "\n");		
					}
			/* comments */
"/*"				{
					int c;
					while((c = yyinput()) != 0)
					{
						if(c == '\n')
							++mylineno;
						else if(c == '*')
						{
							if((c = yyinput()) == '/')
								break;
							else
								unput(c);
						}
					}
					}
"//"				{
					int c;
					++mylineno;
					while((c = yyinput()) != 0)
					{
						if(c == '\n')
							break;
					}
					}
			/* indentifiers */
name					fprintf(yyout, "IDENTIFIER");
			/* operators */
"="						fprintf(yyout, " ASSIGN");
"\+"						fprintf(yyout, " PLUS");
"-"						fprintf(yyout, " MINUS");
"\*"						fprintf(yyout, " MULTIPLY");
"\/"						fprintf(yyout, " DIVIDE");
";"						fprintf(yyout, " SEMICOLON");
			/* keywords */
<<<<<<< HEAD
"break"					fprintf(yyout, " BREAKSYM");
"case"					fprintf(yyout, " CASESYM");
"catch"					fprintf(yyout, " CATCHSYM");
"const"					fprintf(yyout, " CONSTSYM");
"continue"				fprintf(yyout, " CONTSYM");
"debugger"				fprintf(yyout, " DEBUGSYM");
"default"				fprintf(yyout, " DEFAULTSYM");
"delete"				fprintf(yyout, " DELSYM");
"do"					fprintf(yyout, " DOSYM");
"else"					fprintf(yyout, " ELSESYM");
"finally"				fprintf(yyout, " FINALSYM");
"for"					fprintf(yyout, " FORSYM");
"function"				fprintf(yyout, " FUNCSYM");
"if"					fprintf(yyout, " INSYM");
"in"					fprintf(yyout, " INSYM");
"instanceof"				fprintf(yyout, " INSTSYM");
"new"					fprintf(yyout, " NEWSYM");
"return"				fprintf(yyout, " RETURNSYM");
"switch"				fprintf(yyout, " SWITCHSYM");
"throw"					fprintf(yyout, " THROWSYM");
"try"					fprintf(yyout, " TRYSYM");
"TYPEOF"				fprintf(yyout, " TYPEOFSYM");
"var"					fprintf(yyout, " VARSYM");
"void"					fprintf(yyout, " VOIDSYM");
"while"					fprintf(yyout, " WHILESYM");
"with"					fprintf(yyout, " WITH");
			/* Unknown */
.					fprintf(yyout, " UNKNOWN in line %d", mylineno); yyterminate();
=======
"break"					fprintf(yyout, "BREAKSYM");
"case"					fprintf(yyout, "CASESYM");
"catch"					fprintf(yyout, "CATCHSYM");
"const"					fprintf(yyout, "CONSTSYM");
"continue"				fprintf(yyout, "CONTSYM");
"debugger"				fprintf(yyout, "DEBUGSYM");
"default"				fprintf(yyout, "DEFAULTSYM");
"delete"				fprintf(yyout, "DELSYM");
"do"					fprintf(yyout, "DOSYM");
"else"					fprintf(yyout, "ELSESYM");
"finally"				fprintf(yyout, "FINALSYM");
"for"					fprintf(yyout, "FORSYM");
"function"				fprintf(yyout, "FUNCSYM");
"if"					fprintf(yyout, "INSYM");
"in"					fprintf(yyout, "INSYM");
"instanceof"			fprintf(yyout, "INSTSYM");
"new"					fprintf(yyout, "NEWSYM");
"return"				fprintf(yyout, "RETURNSYM");
"switch"				fprintf(yyout, "SWITCHSYM");
"throw"					fprintf(yyout, "THROWSYM");
"try"					fprintf(yyout, "TRYSYM");
"TYPEOF"				fprintf(yyout, "TYPEOFSYM");
"var"					fprintf(yyout, "VARSYM");
"void"					fprintf(yyout, "VOIDSYM");
"while"					fprintf(yyout, "WHILESYM");
"with"					fprintf(yyout, "WITH");
>>>>>>> 2282da19885ba9d7a3817f44840dcb68389b2053
%%

main()
{
	yyin=fopen("test.js", "r");
	yyout=fopen("outtest.txt", "w");
	yylex();
	fclose(yyin);
	fclose(yyout);
}

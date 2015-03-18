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
[\t ]
[\n\r]				{ 
						++mylineno;
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


			/* String */
"\""				{
						int c;
						while((c = yyinput()) != 0)
						{
							if(c == '\n')
								++mylineno;
							else if(c == '\\')
							{
								c = yyinput();
								if(c == '"' || c == '\\')
									continue;
							} else if(c == '"')
								break;
						}
						fprintf(yyout, " STRING");
					}

{number}   			fprintf(yyout, " NUMBER");

		/* operators */
"="					fprintf(yyout, " ASSIGN");
";"					fprintf(yyout, " SEMICOLON");

"\+"				fprintf(yyout, " PLUS");
"-"					fprintf(yyout, " MINUS");
"\*"				fprintf(yyout, " MULTIPLY");
"\/"				fprintf(yyout, " DIVIDE");


		/* keywords */
"break"				fprintf(yyout, " BREAKSYM");
"case"				fprintf(yyout, " CASESYM");
"catch"				fprintf(yyout, " CATCHSYM");
"const"				fprintf(yyout, " CONSTSYM");
"continue"			fprintf(yyout, " CONTSYM");
"debugger"			fprintf(yyout, " DEBUGSYM");
"default"			fprintf(yyout, " DEFAULTSYM");
"delete"			fprintf(yyout, " DELSYM");
"do"				fprintf(yyout, " DOSYM");
"else"				fprintf(yyout, " ELSESYM");
"finally"			fprintf(yyout, " FINALSYM");
"for"				fprintf(yyout, " FORSYM");
"function"			fprintf(yyout, " FUNCSYM");
"if"				fprintf(yyout, " INSYM");
"in"				fprintf(yyout, " INSYM");
"instanceof"		fprintf(yyout, " INSTSYM");
"new"				fprintf(yyout, " NEWSYM");
"return"			fprintf(yyout, " RETURNSYM");
"switch"			fprintf(yyout, " SWITCHSYM");
"throw"				fprintf(yyout, " THROWSYM");
"try"				fprintf(yyout, " TRYSYM");
"TYPEOF"			fprintf(yyout, " TYPEOFSYM");
"var"				fprintf(yyout, " VARSYM");
"void"				fprintf(yyout, " VOIDSYM");
"while"				fprintf(yyout, " WHILESYM");
"with"				fprintf(yyout, " WITH");
					
			/* indentifiers */
{name}				fprintf(yyout, " IDENTIFIER");
			/* Unknown */
.					fprintf(yyout, " UNKNOWN in line %d", mylineno); yyterminate();
%%

main()
{
	yyin=fopen("test.js", "r");
	yyout=fopen("outtest.txt", "w");
	yylex();
	fclose(yyin);
	fclose(yyout);
}

%option noyywrap
%option c++
%{
	#include "stdio.h"
%}

digit	[0-9]
letter	[a-zA-Z]

%%
"+"				{ return PLUS; }
"-"				{ return MINUS; }
"*"				{ return TIMES; }
"/"				{ return SLASH; }
"("				{ return LPAREN }
")"				{ return RPAREN }
";"				{ return SEMICOLON }
","				{ return COMMA }
"."				{ return PERIOD }
"="				{ return BECOMES }
"=="			{ return EQUALS }
"!="			{ return NEQ }
"<"				{ return LSS }
">"				{ return GTR }
"<="			{ return LEQ }
">="			{ return GEQ}
"do"			{ return DOSYM }
"end"			{ return ENDSYM }
"if"			{ return IFSYM }
"then"			{ return THENSYM }
"var"			{ return VARSYM }
"while"			{ return WHILESYM }

[ \t\n\r]	/*skip whitespace */
.			{ printf("Unknown character [%c]\n", yytext[0]);
			return UNKNOWN;	}
%%

int yywrap(void){return 1;}
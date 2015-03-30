%option noyywrap
%option c++
%{
	#include "stdio.h"
%}

digit	[0-9]
letter	[a-zA-Z]

%%
"+"				return PLUS;
"-"				return MINUS;
"*"				return TIMES;
"/"				return SLASH;
"("				return LPAREN;
")"				return RPAREN;
";"				return SEMICOLON;
","				return COMMA;
"."				return PERIOD;
"="				return BECOMES;
"=="			return EQUALS;
"!="			return NEQ;
"<"				return LSS;
">"				return GTR;
"<="			return LEQ;
">="			return GEQ;
"do"			return DOSYM;
"end"			return ENDSYM;
"if"			return IFSYM;
"then"			return THENSYM;
"var"			return VARSYM;
"while"			return WHILESYM;

[ \t\n\r]	    ;
.			    printf("Unknown character [%c]\n", yytext[0]);


//boolean operators
"true"                             parser.restricted = false; return "TRUE";
"false"                            parser.restricted = false; return "FALSE";
"null"                             parser.restricted = false; return "NULL";

//block comments
"/*"(.|\r|\n)*?"*/"                %{
                                        if (yytext.match(/\r|\n/)) {
                                            parser.newLine = true;
                                        }

                                        if (parser.restricted && parser.newLine) {
                                            this.unput(yytext);
                                            parser.restricted = false;
                                            return ";";
                                        }
                                   %}

//line comments
"//".*($|\r\n|\r|\n)               %{
                                        if (yytext.match(/\r|\n/)) {
                                            parser.newLine = true;
                                        }

                                        if (parser.restricted && parser.newLine) {
                                            this.unput(yytext);
                                            parser.restricted = false;
                                            return ";";
                                        }
                                   %}


%%

int yywrap(void){return 1;}
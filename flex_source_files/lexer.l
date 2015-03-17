%option noyywrap
%{
	#include "stdio.h"
%}

digit	[0-9]
letter	[a-zA-Z]
name	({letter}|{digit}|\$)({letter}|{digit}|[_.\-/$])*
num1	[-+]?{digit}+\.?([eE][-+]?{digit}+)?
num2	[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
number	{num1}|{num2}

%%

[ \t\n\r]			/* removes whitespace */

%%
%option noyywrap
%{
	#include "stdio.h"
	int mylineno = 0;
%}

digit	[0-9]
letter	[a-zA-Z]
name	({letter}|{digit}|\$)({letter}|{digit}|[_.\-/$])*
num1	[-+]?{digit}+\.?([eE][-+]?{digit}+)?
num2	[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
number	{num1}|{num2}

%%

[ \t\n\r]			/* removes whitespace */

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
					while((c = yyinput()) != 0)
					{
						if(c == '\n')
							break;
					}
					}


%%
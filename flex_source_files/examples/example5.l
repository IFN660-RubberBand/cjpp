/* LEX program to identify a compound statement */
%option noyywrap
%{
#include"stdio.h"
int count=0;
%}

%%
" [aA][nN][dD] " count ++;
" [oO][rR] " count++;
" [bB][uU][tT] " count++;
%%

main()
{
yylex();
if( count != 0 )
printf("\nIt is a compound statement");
else
printf("\nIts is a Simple statement"); 
}

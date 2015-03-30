/* LEX program to recognize a valid arithmetic expression */
%option noyywrap
%{
/* No. of operators and operands */
int nop=0,noprnd=0,top=-1,stack[20];
%}

%%
[0-9]*|[a-zA-Z]* noprnd++; /* Increment no. of operand */
[+-/*%] nop++;                /* Increment no. of operator */
"(" { stack[++top]='(';}
")" { if((stack[top]='(')&&(top!=-1)) top--; }
%%

#include"stdio.h"
int main()
{
    printf("\n*** Enter an expression ***\n");
    yylex();
    if ((nop != (noprnd - 1)) || ( top==-1))
        printf("\nIt's an INVALID statement");
    else
    {
        printf("\nIt's a VALID statement");
        printf("\nNumber of operators = %d",nop);
    }
    return 0;
}

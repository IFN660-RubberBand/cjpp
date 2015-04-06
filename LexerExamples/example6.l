/* Program to count number of printf's and scanf's in a given program */
%option noyywrap
%{
#include"stdio.h"
int pcount=0;
int scount=0;
%}


%%
"printf" fprintf(yyout,"write");pcount++;
"scanf" fprintf(yyout,"read");scount++;
%%

main()
{
    yyin=fopen("tester.c","r");
    yyout=fopen("otester","w");
    yylex();
    printf("\nprintf count=%d\nscanf count=%d\n",pcount,scount);
    fclose(yyin);
    fclose(yyout);
}

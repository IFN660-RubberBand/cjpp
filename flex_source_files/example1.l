/* Program to count number of lines, words, characters and blank spaces*/


%{
int cha=0;
int words=0;
int lines=0;
int blanks=0;
%}

%%
\n lines++ ; 
[ \t] cha++; blanks++;
[a-zA-Z0-9] cha++;
[a-zA-Z0-9]/[ \n] words++; cha++;
. cha++;
%%

main()
{
    yylex();
    printf("characters=%d\n",cha);
    printf("words=%d\n",words);
    printf("lines=%d\n",lines);
    printf("blanks=%d\n",blanks);
}

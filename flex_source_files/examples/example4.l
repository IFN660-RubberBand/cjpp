/* LEX program to count the number of identifiers */
%option noyywrap
%{
int id_ct=0;
%}


SPC [ \t]*
IDE [a-zA-Z_][a-zA-Z0-9_]*
DEC "int "|"float "|"char "|"long "|"unsigned "
%s DEFN

%%
{SPC}{DEC}{SPC} {BEGIN(DEFN);}
<DEFN>{IDE}{SPC}\,{SPC} {id_ct++;}
<DEFN>{IDE}{SPC}\;{SPC} {id_ct++;BEGIN(INITIAL);}
<*>./\n+;
.;
%%

main(int argc,char *argv[])
{
    yyin=fopen(argv[1],"r");
    yylex();
    printf("\nNumber of identifiers is %d\n",id_ct);
}

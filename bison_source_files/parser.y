%{
#include <stdio.h>
#include <stdlib.h>

int yywrap()
{
	return 1;
}


%token <num> NUMBER
%token <hexnum> HEXNUMBER
%token <id> IDENTIFIER
%token <word> STRING
/* tokens for keywords */

%type <num> line exp term
%type <hexnum>
%type <id> assignment
%type <word> 

%%

	/* grammer goes here */


%%

main()
{
	yyparse();
}

void yyerror(const char *s)
{
	fprintf(stderr,"error: %s\n",s);
}
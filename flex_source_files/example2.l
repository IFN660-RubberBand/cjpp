/* Program in LEX to count the number of vowels and consonants in a given string. */

%{
/* No. of Vowels, Consonants & Blank characters */ 
int nvow=0,ncons=0,nblank=0;
%}


%%
[aeiouAEIOU] nvow++;                              /* Increment the no. of Vowels */
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] ncons++;        /* Increment the no. of Consonants */
[ ] nblank++;                                    /* Increment the no. of BlankSpace */
%%


#include"stdio.h"
int main()
{
    printf("\nEnter the string : ");
    yylex();
    printf("\n\nNo. of Vowels = %d",nvow);
    printf("\n\nNo. of Consonants = %d",ncons);
    printf("\n\nNo. of Blank Spaces = %d\n",nblank);
    return 0;
}

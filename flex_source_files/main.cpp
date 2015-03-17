#include <stdio.h>
#include <iostream>

extern int yylex(void);
extern FILE* yyin;

int main()
{
	yyin = fopen("test.js", "r");
	std::cout << yylex() << "\n";
}
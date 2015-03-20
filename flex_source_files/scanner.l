%option noyywrap

%{
	#include "stdio.h"
	#include <string.h>
	//#include "parser.tab.h"
	
	int mylineno = 1;
	void yyerror(char *message)
	{
 		 printf("Error: %s\n",message);
	}
%}

%x STRING1
%x STRING2

digit		[0-9]
hexdigit	[0-9a-fA-F]
letter		[a-zA-Z]
name		({letter}|{digit}|\$)({letter}|{digit}|[_.\-/$])*


hexnumber	0x{hexdigit}+
num1		[-+]?{digit}+\.?([eE][-+]?{digit}+)?
num2		[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
number		{num1}|{num2}

%%
			/* whitespace */
[\t ]
[\n\r]				{ 
						++mylineno;
					  	fprintf(yyout, "\n");		
					}
					
					
			/* comments */
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
						++mylineno;
						while((c = yyinput()) != 0)
						{
							if(c == '\n')
								break;
						}
					}


			/* String - looks stupid, but works*/
\"   BEGIN(STRING1);

<STRING1>[^\\\n"]*  yymore();
<STRING1><<EOF>>    yyerror("EOF in string.");       BEGIN(INITIAL);
<STRING1>\n         fprintf(yyout, "unterminated string line %d", mylineno); BEGIN(INITIAL);
<STRING1>\\[\\nt"\n] yymore();
<STRING1>\\			fprintf(yyout, "incorrect escaped character in line %d", mylineno); yyterminate();
<STRING1>\"        {
                     yytext[yyleng-1] = '\0';
                     fprintf(yyout, " STRING(%s)", yytext, yyleng); BEGIN(INITIAL);
                  }

\'   BEGIN(STRING2);

<STRING2>[^\\\n']*  yymore();
<STRING2><<EOF>>    yyerror("EOF in string.");       BEGIN(INITIAL);
<STRING2>\n         fprintf(yyout, "unterminated string line %d", mylineno); BEGIN(INITIAL);
<STRING2>\\[\\nt'\n] yymore();
<STRING2>\\			fprintf(yyout, "incorrect escaped character in line %d", mylineno); yyterminate();
<STRING2>\'        {
                     yytext[yyleng-1] = '\0';
                     fprintf(yyout, " STRING(%s)", yytext, yyleng); BEGIN(INITIAL);
				  }						  
				  		

{number}   			fprintf(yyout, " NUMBER(%f)", strtod( yytext , NULL ));
{hexnumber}			fprintf(yyout, " HEXNUMBER(%f)", (double) strtol(yytext+2, NULL, 16));
		
	
";"					fprintf(yyout, " SEMICOLON");	
":"					fprintf(yyout, " COLON");	
","					fprintf(yyout, " COMMA");		
"."					fprintf(yyout, " POINT");
"?"					fprintf(yyout, " QUESTION");
		
		/* operators */
"\+"				fprintf(yyout, " PLUS");
"\+\+"				fprintf(yyout, " INC");
"-"					fprintf(yyout, " MINUS");
"--"			 	fprintf(yyout, " DEC");
"\*"				fprintf(yyout, " MULTIPLY");	 
"\/"				fprintf(yyout, " DIVIDE");	
"%"					fprintf(yyout, " MOD");		
 
		/* all assignments */ 
"="					fprintf(yyout, " ASSIGN");	
"\+="				fprintf(yyout, " ASSPLUS");
"-="				fprintf(yyout, " ASSMINUS");
"\*="				fprintf(yyout, " ASSMULTIPLY");	 
"\/="				fprintf(yyout, " ASSDIVIDE");	
"%="				fprintf(yyout, " ASSMOD");		
"^="				fprintf(yyout, " ASSBITXOR");
"|="				fprintf(yyout, " ASSBITOR");		
"&="				fprintf(yyout, " ASSBITAND");
"<<="				fprintf(yyout, " ASSLSHIFT");
">>="				fprintf(yyout, " ASSRSHIFT");
">>>="				fprintf(yyout, " ASSLRSHIFT");

		/* comperator */
"=="				fprintf(yyout, " EQUAL");
"==="				fprintf(yyout, " IDENT");
"!="				fprintf(yyout, " NEQ");
"!=="				fprintf(yyout, " NIDENT");
"<"					fprintf(yyout, " LSS");
">"					fprintf(yyout, " GTR");
"<="				fprintf(yyout, " LEQ");
">="				fprintf(yyout, " GEQ");

		/* shift operation */
"<<"				fprintf(yyout, " LSHIFT");
">>"				fprintf(yyout, " RSHIFT");
">>>"				fprintf(yyout, " LRSHIFT");

		/* logic operator */ 
"!"					fprintf(yyout, " NOT");
"||"				fprintf(yyout, " OR");		
"&&"				fprintf(yyout, " AND");		

		/* bitwise operator */ 
"^"					fprintf(yyout, " BITXOR");
"|"					fprintf(yyout, " BITOR");		
"&"					fprintf(yyout, " BITAND");
"~"					fprintf(yyout, " BITNOT");

		/* boolean constants */
"false"				fprintf(yyout, " FALSE");
"true"				fprintf(yyout, " TRUE");
	
		/* null literal */
"null"				fprintf(yyout, " NULL");
		
		/* brackets */
"("					fprintf(yyout, " LPAREN"); 		 
")"					fprintf(yyout, " RPAREN"); 		 
"["					fprintf(yyout, " LBRACK"); 		 
"]"					fprintf(yyout, " RBRACK"); 		 
"{"					fprintf(yyout, " LCURLY"); 		 
"}"					fprintf(yyout, " RCURLY"); 		 
		

		/* keywords */
"break"				fprintf(yyout, " BREAKSYM"); 	
"case"				fprintf(yyout, " CASESYM");		 
"catch"				fprintf(yyout, " CATCHSYM");	 
"continue"			fprintf(yyout, " CONTSYM");		 
"debugger"			fprintf(yyout, " DEBUGSYM");	 
"default"			fprintf(yyout, " DEFAULTSYM");	
"delete"			fprintf(yyout, " DELSYM");		 
"do"				fprintf(yyout, " DOSYM");		 
"else"				fprintf(yyout, " ELSESYM");		
"finally"			fprintf(yyout, " FINALSYM");	 
"for"				fprintf(yyout, " FORSYM");		 
"function"			fprintf(yyout, " FUNCSYM");		 
"if"				fprintf(yyout, " IFSYM");		 
"in"				fprintf(yyout, " INSYM");		 
"instanceof"		fprintf(yyout, " INSTSYM");		 
"new"				fprintf(yyout, " NEWSYM");		 
"return"			fprintf(yyout, " RETURNSYM");	 
"switch"			fprintf(yyout, " SWITCHSYM");	 
"this"				fprintf(yyout, " THISSYM");		 
"throw"				fprintf(yyout, " THROWSYM");	 
"try"				fprintf(yyout, " TRYSYM");		 
"typeof"			fprintf(yyout, " TYPEOFSYM");	 
"var"				fprintf(yyout, " VARSYM");		 
"void"				fprintf(yyout, " VOIDSYM");		 
"while"				fprintf(yyout, " WHILESYM");	 
"with"				fprintf(yyout, " WITHSYM");		 
		
		/* future reserved keywords */
"class"				yyerror("Usage of reserved keyword 'class'");
"enum"				yyerror("Usage of reserved keyword 'enum'");
"extends"			yyerror("Usage of reserved keyword 'extends'");
"super"				yyerror("Usage of reserved keyword 'super'");
"const"				yyerror("Usage of reserved keyword 'const'");
"export"			yyerror("Usage of reserved keyword 'export'");
"import" 			yyerror("Usage of reserved keyword 'import'");
		
					
			/* indentifiers */
{name}				fprintf(yyout, " IDENTIFIER(%s)", yytext);
			/* Unknown */
.					fprintf(yyout, " unknown identifier %s in line %d", yytext, mylineno); yyterminate();
%%
main()
{
	yyin=fopen("test.js", "r");
	yyout=fopen("outtest.txt", "w");
	yylex();
	fclose(yyin);
	fclose(yyout);
}
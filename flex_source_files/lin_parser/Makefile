all:
	
	flex scanner.l
	yacc -d parser.y -o parser.tab.c
	g++ lex.yy.c parser.tab.h parser.tab.c -o scanner
	./scanner < sample.js

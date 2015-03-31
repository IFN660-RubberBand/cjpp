all:
	
	flex scanner.l
	yacc -d parser.y -o parser.tab.c
	gcc lex.yy.c parser.tab.h parser.tab.c -o scanner
	./scanner

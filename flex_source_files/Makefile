ifdef SystemRoot
	#Windows
	lex = win_flex
	yacc = win_bison
	main = scanner.exe
else
	#Cygwin/MinGW or Unix
	UNAME := $(shell uname)
endif


ifeq ($(UNAME), Linux)
	#Linux
	lex = flex
	yacc = yacc
	main = scanner
endif
ifeq ($(UNAME), Darwin)
	#MacOS
	lex = lex
	yacc = yacc
	main = scanner
endif
ifeq ($(UNAME), MINGW32_NT-6.1)
	#MinGW
	lex = win_flex
	yacc = win_bison
	main = scanner.exe
endif


all: $(main)

$(main): lex.yy.c parser.tab.c parser.tab.h
	g++ lex.yy.c parser.tab.h parser.tab.c -o $(main)

lex.yy.c: scanner.l
	$(lex) scanner.l

parser.tab.c: parser.y
	$(yacc) -d parser.y -o parser.tab.c

clean:
	rm -f $(main) lex.yy.c parser.tab.c parser.tab.h

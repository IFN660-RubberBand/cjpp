ifeq ($(UNAME), Linux)
	lex = win_flex
	yacc = win_bison
	main = scanner.exe
else
	lex = win_flex
	yacc = win_bison
	main = scanner.exe
endif


all: $(main)

$(main): lex.yy.c parser.tab.c parser.tab.h
	$(info uname = $(UNAME))
	g++ lex.yy.c parser.tab.h parser.tab.c -o $(main)

lex.yy.c: scanner.l
	$(lex) scanner.l
	
parser.tab.c: parser.y
	$(yacc) -d parser.y	

clean:
	 
	rm -f $(main) lex.yy.c parser.tab.c
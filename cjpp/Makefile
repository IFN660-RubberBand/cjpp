ifdef SystemRoot
	#Windows
	lex = win_flex
	yacc = win_bison
	main = cjpp.exe
else
	#Cygwin/MinGW or Unix
	UNAME := $(shell uname)
endif


ifeq ($(UNAME), Linux)
	#Linux
	lex = flex
	yacc = yacc
	main = cjpp
endif
ifeq ($(UNAME), Darwin)
	#MacOS
	lex = lex
	yacc = yacc
	main = cjpp
endif
ifeq ($(UNAME), MINGW32_NT-6.1)
	#MinGW
	lex = win_flex
	yacc = win_bison
	main = cjpp.exe
endif

########

all: $(main)

$(main): $(main).yy.c $(main).tab.c
	g++ -x c++ $(main).yy.c $(main).tab.c -o $(main)

$(main).tab.c: $(main).y
	yacc -d $(main).y -o $(main).tab.c

$(main).yy.c: $(main).l
	lex -o $(main).yy.c $(main).l

clear:
	rm $(main).yy.c $(main).tab.c $(main).tab.h $(main)

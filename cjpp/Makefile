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
H_FILES := $(wildcard ast/*.h)



all: $(main)

$(main): cjpp.yy.c cjpp.tab.c cjpp.tab.h $(H_FILES)
	g++ -x c++ -std=c++11 cjpp.yy.c cjpp.tab.c -o $(main)

cjpp.tab.c: cjpp.y
	$(yacc) -d --verbose cjpp.y -o cjpp.tab.c

cjpp.yy.c: cjpp.l
	$(lex) -o cjpp.yy.c cjpp.l

clean:
	rm cjpp.yy.c cjpp.tab.c cjpp.tab.h $(main)

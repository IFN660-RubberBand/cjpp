# flex
C++ code for implementing Flex

1) Add the "lexer.l" file to the same directory as "win_flex.exe"

2) In command prompt, run "win_flex.exe" with the argument "lexer.l"

3) lex.yy.c file should be generated in the same directory

4) To compile to create the scanner, move the lex.yy.c and the main.cpp to the same directory as g++.exe

5) In command prompt, run "g++ lex.yy.c main.cpp" and it should generate the a.exe file

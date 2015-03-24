# flex
C++ code for implementing Flex

1) Compile "scanner.l" using command promt "flex scanner.l"

2) lex.yy.c file should be generated in the same directory

3) To compile the flex file, in command prompt run "g++ lex.yy.c -lfl" and it should generate the a.exe file

4) The scanner then can be tested using "a.exe < test.js"

5) Check the output file to see if it tokenised the test file

flex src/lexer.l
bison -d src/parser.ypp
g++ -ll src/parser.tab.cpp src/lex.yy.c
./a.out $1
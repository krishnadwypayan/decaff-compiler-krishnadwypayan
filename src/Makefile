parser: lexer.l parser.ypp 
		flex lexer.l
		bison -d parser.ypp
		g++ -o parser parser.tab.cpp lex.yy.c -ll
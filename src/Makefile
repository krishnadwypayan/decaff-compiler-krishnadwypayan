parser: lexer.l parser.ypp
		flex lexer.l
		bison -v -d parser.ypp
		g++ -o parser -IHeaders parser.tab.cpp lex.yy.c program.cpp fieldDeclarations.cpp methodDeclarations.cpp block.cpp statements.cpp -ll

clean:
	rm parser.tab.cpp parser.tab.hpp parser.output lex.yy.c parser
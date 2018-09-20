/* just like Unix wc */
%{
	int chars = 0;
	int words = 0;
	int lines = 0;
%}

%%

"+" { printf("PLUS\n"); }
"-" { printf("MINUS\n"); }
"*" { printf("TIMES\n"); }
"/" { printf("DIVIDE\n"); }
"|" { printf("ABS\n"); }
[0-9]+ { printf("NUMBER %s\n", yytext); }
\n { printf("NEWLINE\n"); }
[ \t] { }
. { printf("Mystery character %s\n", yytext); }

%%

main(int argc, char **argv)
{
	yylex();
	; printf("%8d%8d%8d\n", lines, words, chars);
}
%{
	#include "program.h"
	#include "parser.tab.hpp"
	#define YY_DECL extern "C" int yylex()
	extern union Node yylval;
	int line_num = 1;
%}

digit [0-9]
alpha [a-zA-Z_]
alpha_num {alpha}|{digit}
hex_digit {digit}|[a-fA-F]
char [ -~]			
char_literal \'{char}\'
string_literal \"{char}*\"
decimal_literal {digit}{digit}*
hex_literal "0x"{hex_digit}{hex_digit}*
int_literal {decimal_literal}|{hex_literal}

%%

"class"     		{ return CLASS; }
"void"      		{ return VOID; }
"int"|"boolean"		{ yylval.value = strdup(yytext); return TYPE; }
"callout"			{ return CALLOUT; }
"return"    		{ return RETURN; }
"for"				{ return FOR; }
"if"        		{ return IF; }
"else"      		{ return ELSE; }
"break"     		{ return BREAK; }
"continue"  		{ return CONTINUE; }
"true"|"false"		{ yylval.value = strdup(yytext); return BOOL_LITERAL; }

";"         { return SEMI_COLON; }
","         { return COMMA; }
"["         { return OSB; }
"]"         { return CSB; }
"("         { return OP; }
")"         { return CP; }
"{"         { return OFB; }
"}"         { return CFB; }

"="         { return EQUAL; }
"!="		{ return NOT_EQUAL; }
"+="        { return PLUS_EQUAL; }
"-="        { return MINUS_EQUAL; }
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"<"         { return LT; }
">"         { return GT; }
"<="        { return LE; }
">="        { return GE; }
"=="        { return EQUAL_EQUAL; }
"&&"        { return COND_AND; }
"||"        { return COND_OR; }

{alpha}{alpha_num}*		{ yylval.value = strdup(yytext); return ID; }
{char_literal} 			{ yylval.value = strdup(yytext); return CHAR_LITERAL; }
{string_literal} 		{ yylval.value = strdup(yytext); return STRING_LITERAL; }
{int_literal} 			{ yylval.number = atoi(yytext); return INT_LITERAL; }

\n 	{ line_num++; printf("\n\n**************** :: %d :: *****************\n", line_num);}

"//".* 		/* ignore comments */
[ \t]+		/* ignore delimiters */

%%
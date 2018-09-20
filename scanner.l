
%{
    
    /* Global variable: yylval
     * -----------------------
     * This global variable is how we get attribute information about the token
     * just scanned to the client. The scanner sets the global variable
     * appropriately and since it's global the client can just read it.  In the
     * future, this variable will be declared for us in the y.tab.c file
     * produced by Yacc, but for now, we declare it manually.
     */
    YYSTYPE yylval;
    
    /* Global variable: yylloc
     * -----------------------
     * This global variable is how we get position information about the token
     * just scanned to the client. (Operates similarly to yylval above)
     */
    struct yyltype yylloc;
    
%}

EXPONENT    [eE][+-]?[0-9]+

%%

/* Keywords */
"class"     { return T_Class; }
"void"      { return T_Void; }
"int"       { return T_Int; }
"boolean"   { return T_Boolean; }
"if"        { return T_If; }
"else"      { return T_Else; }
"break"     { return T_Break; }
"continue"  { return T_Continue; }
"return"    { return T_Return; }

/* Operators and punctuations */
"="         { return T_Equal; }
"+="        { return T_PlusEqual; }
"-="        { return T_MinusEqual; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }
"<"         { return '<'; }
">"         { return '>'; }
"<="        { return T_LesserEqual; }
">="        { return T_GreaterEqual; }
"=="        { return T_EqualEqual; }
"!="        { return T_NotEqual; }
"&&"        { return T_And; }
"||"        { return T_Or; }
"!"         { return '!'; }
";"         { return ';'; }
","         { return ','; }
"."         { return '.'; }
"["         { return '['; }
"]"         { return ']'; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }

/* constants */
[ \t]       { }    // whitespace
\n          { lineNum++;  columnLeft = columnRight = 1; }    // newlines.  reset columns since we moved to a newline

"true"      {
                // bool constant
                yylval.boolConstant = true;
                return T_BoolConstant;
            }

"false"     {
                // bool constant
                yylval.boolConstant = false;
                return T_BoolConstant;
            }

[a-zA-Z][a-zA-Z0-9_]*
            {
                // identifier limited to 31 characters
                strncpy(yylval.identifier, yytext, MaxIdentLen);
                //make sure identifier is null terminated if token was longer than 31
                yylval.identifier[MaxIdentLen] = '\0';
                if (yyleng > MaxIdentLen) {
                    ReportError::LongIdentifier(&yylloc, yytext);
                }
                return T_Identifier;
            }

[0-9]+     {
                // decimal int constants
                yylval.integerConstant = atoi(yytext);
                return T_IntConstant;
            }

0[xX][0-9a-fA-F]+
            {
                // hex int constants
                yylval.integerConstant = strtol(yytext, NULL, 16);
                return T_IntConstant;
            }

[0-9]+\.[0-9]*{EXPONENT}?
            {
                // double constant
                yylval.doubleConstant = strtod(yytext, NULL);
                return T_DoubleConstant;
            }

\"[^\n"]*\"
            {
                // string constant
                yylval.stringConstant = yytext;
                return T_StringConstant;
            }

/* catch errors*/
\"[^"\n]*   { ReportError::UntermString(&yylloc, yytext); } // find unmatched quotes

/* catch all other characters */
.           { ReportError::UnrecogChar(&yylloc, yytext[0]); }

%%

main() {
    
}

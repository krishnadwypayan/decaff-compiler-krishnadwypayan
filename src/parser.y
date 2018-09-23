%{
%}

%start program

/* -------------------- Tokens ----------------------- */
%token CLASS
%token VOID TYPE
%token CALLOUT RETURN
$token FOR IF ELSE
%token BREAK CONTINUE
%token SEMI_COLON COMMA
%token OSB CSB OP CP OFB CFB
%token EQUAL PLUS_EQUAL MINUS_EQUAL
%token ADD SUB DIV MUL MOD
%token LT GT LE GE
%token EQUAL_EQUAL NOT_EQUAL
%token COND_AND COND_OR NOT
%token ID
%token CHAR_LITERAL STRING_LITERAL DECIMAL_LITERAL HEX_LITERAL INT_LITERAL BOOL_LITERAL

/* ---------------- Left Precedence	----------------- */
%left EQUAL NOT_EQUAL
%left COND_AND COND_OR
%left LT GT LE GE
%left ADD SUB MUL DIV MOD
%nonassoc NOT

/* ----------------- Grammar Rules ------------------ */
%%

program:
	CLASS ID OFB field_declarations method_declarations CFB;

field_declarations:
	/* epsilon */
	| field_declarations field_declaration SEMI_COLON
	;

field_declaration:
	TYPE vars
	;

vars:
	var
	| vars COMMA var
	;

var:
	ID
	| ID OSB INT_LITERAL CSB

method_declarations:
	/* epsilon */
	| method_declaration method_declarations
	;

method_declaration:
	TYPE ID OP method_args CP block
	| VOID ID OP method_args CP block
	;

method_args:
	OP CP
	| OP TYPE ID method_arg CP
	;

method_arg:
	/* epsilon */
	| COMMA TYPE ID method_arg
	;

block:
	OFB var_declarations statements CFB
	;

var_declarations:
	TYPE ID more_var_decl
	;

more_var_decl:
	/* epsilon */
	| COMMA ID more_var_decl
	;

statements:
	/* epsilon */
	| statements statement
	;

statement:
	location assign_op expr SEMI_COLON
	| method_call SEMI_COLON
	| IF OP expr CP block
	| IF OP expr CP block ELSE block
	| FOR ID EQUAL expr COMMA expr block
	| RETURN SEMI_COLON
	| RETURN expr SEMI_COLON
	| BREAK SEMI_COLON
	| CONTINUE SEMI_COLON
	| block

assign_op:
	EQUAL
	| PLUS_EQUAL
	| MINUS_EQUAL
	;

method_call:
	method_name OP method_call_params CP
	| CALLOUT OP STRING_LITERAL callout_args CP
	;

method_name:
	ID
	;

method_call_params:
	expr
	| method_call_params COMMA expr
	;

callout_args:
	callout_arg
	| callout_args COMMA callout_arg
	;

callout_arg:
	expr
	| STRING_LITERAL
	;

location:
	ID 
	| ID OSB expr CSB
	;

expr:
	location
	| method_call
	| literal
	| expr bin_op expr
	| SUB expr
	| NOT expr
	| OP expr CP
	;

literal:
	INT_LITERAL
	| CHAR_LITERAL
	| BOOL_LITERAL
	;

bin_op:
	arith_op
	| rel_op
	| eq_op
	| cond_op
	;

arith_op:
	ADD 
	| SUB 
	| MUL
	| DIV
	| MOD
	;

rel_op:
	LT
	| GT
	| LE
	| GE
	;

eq_op:
	EQUAL_EQUAL
	| NOT_EQUAL
	;

cond_op:
	COND_AND
	| COND_OR
	;

%%
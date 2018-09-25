/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     VOID = 259,
     TYPE = 260,
     CALLOUT = 261,
     RETURN = 262,
     FOR = 263,
     IF = 264,
     ELSE = 265,
     BREAK = 266,
     CONTINUE = 267,
     SEMI_COLON = 268,
     COMMA = 269,
     OSB = 270,
     CSB = 271,
     OP = 272,
     CP = 273,
     OFB = 274,
     CFB = 275,
     EQUAL = 276,
     PLUS_EQUAL = 277,
     MINUS_EQUAL = 278,
     ADD = 279,
     SUB = 280,
     DIV = 281,
     MUL = 282,
     MOD = 283,
     LT = 284,
     GT = 285,
     LE = 286,
     GE = 287,
     EQUAL_EQUAL = 288,
     NOT_EQUAL = 289,
     COND_AND = 290,
     COND_OR = 291,
     NOT = 292,
     ID = 293,
     CHAR_LITERAL = 294,
     STRING_LITERAL = 295,
     INT_LITERAL = 296,
     BOOL_LITERAL = 297
   };
#endif
/* Tokens.  */
#define CLASS 258
#define VOID 259
#define TYPE 260
#define CALLOUT 261
#define RETURN 262
#define FOR 263
#define IF 264
#define ELSE 265
#define BREAK 266
#define CONTINUE 267
#define SEMI_COLON 268
#define COMMA 269
#define OSB 270
#define CSB 271
#define OP 272
#define CP 273
#define OFB 274
#define CFB 275
#define EQUAL 276
#define PLUS_EQUAL 277
#define MINUS_EQUAL 278
#define ADD 279
#define SUB 280
#define DIV 281
#define MUL 282
#define MOD 283
#define LT 284
#define GT 285
#define LE 286
#define GE 287
#define EQUAL_EQUAL 288
#define NOT_EQUAL 289
#define COND_AND 290
#define COND_OR 291
#define NOT 292
#define ID 293
#define CHAR_LITERAL 294
#define STRING_LITERAL 295
#define INT_LITERAL 296
#define BOOL_LITERAL 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "src/parser.ypp"
{
	int number;
	char *value;
}
/* Line 1529 of yacc.c.  */
#line 138 "parser.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


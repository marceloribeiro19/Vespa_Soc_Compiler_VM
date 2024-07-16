/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ASM_PARSER_TAB_H_INCLUDED
# define YY_YY_ASM_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_ADD = 258,               /* TOKEN_ADD  */
    TOKEN_SUB = 259,               /* TOKEN_SUB  */
    TOKEN_OR = 260,                /* TOKEN_OR  */
    TOKEN_AND = 261,               /* TOKEN_AND  */
    TOKEN_NOT = 262,               /* TOKEN_NOT  */
    TOKEN_XOR = 263,               /* TOKEN_XOR  */
    TOKEN_CMP = 264,               /* TOKEN_CMP  */
    TOKEN_BRANCH = 265,            /* TOKEN_BRANCH  */
    TOKEN_JUMP = 266,              /* TOKEN_JUMP  */
    TOKEN_JUMP_LINK = 267,         /* TOKEN_JUMP_LINK  */
    TOKEN_MOVE = 268,              /* TOKEN_MOVE  */
    TOKEN_LOAD_DIRECT = 269,       /* TOKEN_LOAD_DIRECT  */
    TOKEN_LOAD_IMMEDIATE = 270,    /* TOKEN_LOAD_IMMEDIATE  */
    TOKEN_LOAD_INDEXED = 271,      /* TOKEN_LOAD_INDEXED  */
    TOKEN_STORE_DIRECT = 272,      /* TOKEN_STORE_DIRECT  */
    TOKEN_STORE_INDEXED = 273,     /* TOKEN_STORE_INDEXED  */
    TOKEN_PUSH = 274,              /* TOKEN_PUSH  */
    TOKEN_POP = 275,               /* TOKEN_POP  */
    TOKEN_RETI = 276,              /* TOKEN_RETI  */
    TOKEN_HALT = 277,              /* TOKEN_HALT  */
    TOKEN_NOP = 278,               /* TOKEN_NOP  */
    TOKEN_NUMBER = 279,            /* TOKEN_NUMBER  */
    TOKEN_REG = 280,               /* TOKEN_REG  */
    TOKEN_IDENTIFIER = 281,        /* TOKEN_IDENTIFIER  */
    TOKEN_ENDFILE = 282,           /* TOKEN_ENDFILE  */
    TOKEN_ERROR = 283,             /* TOKEN_ERROR  */
    TOKEN_COMMA = 284,             /* TOKEN_COMMA  */
    TOKEN_CARDINAL = 285,          /* TOKEN_CARDINAL  */
    TOKEN_COLON = 286,             /* TOKEN_COLON  */
    TOKEN_DOLLAR = 287,            /* TOKEN_DOLLAR  */
    TOKEN_BYTE = 288,              /* TOKEN_BYTE  */
    TOKEN_WORD = 289,              /* TOKEN_WORD  */
    TOKEN_ALLOC = 290,             /* TOKEN_ALLOC  */
    TOKEN_ORG = 291,               /* TOKEN_ORG  */
    TOKEN_EQU = 292,               /* TOKEN_EQU  */
    TOKEN_PLUS = 293,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 294,             /* TOKEN_MINUS  */
    TOKEN_LEFT_PAREN = 295,        /* TOKEN_LEFT_PAREN  */
    TOKEN_RIGHT_PAREN = 296        /* TOKEN_RIGHT_PAREN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ASM_PARSER_TAB_H_INCLUDED  */

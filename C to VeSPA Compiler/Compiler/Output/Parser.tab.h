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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 11 "Parser/Parser.y"

#include "../Util/Globals.h"

#line 53 "Parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_IF = 258,                /* TOKEN_IF  */
    TOKEN_EOF = 259,               /* TOKEN_EOF  */
    TOKEN_ERROR = 260,             /* TOKEN_ERROR  */
    TOKEN_ELSE = 261,              /* TOKEN_ELSE  */
    TOKEN_DO = 262,                /* TOKEN_DO  */
    TOKEN_WHILE = 263,             /* TOKEN_WHILE  */
    TOKEN_FOR = 264,               /* TOKEN_FOR  */
    TOKEN_SWITCH = 265,            /* TOKEN_SWITCH  */
    TOKEN_CASE = 266,              /* TOKEN_CASE  */
    TOKEN_DEFAULT = 267,           /* TOKEN_DEFAULT  */
    TOKEN_RETURN = 268,            /* TOKEN_RETURN  */
    TOKEN_BREAK = 269,             /* TOKEN_BREAK  */
    TOKEN_INT = 270,               /* TOKEN_INT  */
    TOKEN_FLOAT = 271,             /* TOKEN_FLOAT  */
    TOKEN_DOUBLE = 272,            /* TOKEN_DOUBLE  */
    TOKEN_CHAR = 273,              /* TOKEN_CHAR  */
    TOKEN_VOID = 274,              /* TOKEN_VOID  */
    TOKEN_STRUCT = 275,            /* TOKEN_STRUCT  */
    TOKEN_TYPEDEF = 276,           /* TOKEN_TYPEDEF  */
    TOKEN_CONTINUE = 277,          /* TOKEN_CONTINUE  */
    TOKEN_EXTERN = 278,            /* TOKEN_EXTERN  */
    TOKEN_GOTO = 279,              /* TOKEN_GOTO  */
    TOKEN_LONG = 280,              /* TOKEN_LONG  */
    TOKEN_ENUM = 281,              /* TOKEN_ENUM  */
    TOKEN_SHORT = 282,             /* TOKEN_SHORT  */
    TOKEN_SIZEOF = 283,            /* TOKEN_SIZEOF  */
    TOKEN_STATIC = 284,            /* TOKEN_STATIC  */
    TOKEN_SIGNED = 285,            /* TOKEN_SIGNED  */
    TOKEN_UNION = 286,             /* TOKEN_UNION  */
    TOKEN_UNSIGNED = 287,          /* TOKEN_UNSIGNED  */
    TOKEN_VOLATILE = 288,          /* TOKEN_VOLATILE  */
    TOKEN_ASSIGN = 289,            /* TOKEN_ASSIGN  */
    TOKEN_PLUS = 290,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 291,             /* TOKEN_MINUS  */
    TOKEN_OVER = 292,              /* TOKEN_OVER  */
    TOKEN_PERCENT = 293,           /* TOKEN_PERCENT  */
    TOKEN_LEFT_PARENTHESES = 294,  /* TOKEN_LEFT_PARENTHESES  */
    TOKEN_RIGHT_PARENTHESES = 295, /* TOKEN_RIGHT_PARENTHESES  */
    TOKEN_LEFT_BRACE = 296,        /* TOKEN_LEFT_BRACE  */
    TOKEN_RIGHT_BRACE = 297,       /* TOKEN_RIGHT_BRACE  */
    TOKEN_LEFT_BRACKET = 298,      /* TOKEN_LEFT_BRACKET  */
    TOKEN_RIGHT_BRACKET = 299,     /* TOKEN_RIGHT_BRACKET  */
    TOKEN_TERNARY = 300,           /* TOKEN_TERNARY  */
    TOKEN_SEMI = 301,              /* TOKEN_SEMI  */
    TOKEN_COLON = 302,             /* TOKEN_COLON  */
    TOKEN_COMMA = 303,             /* TOKEN_COMMA  */
    TOKEN_INCREMENT = 304,         /* TOKEN_INCREMENT  */
    TOKEN_DECREMENT = 305,         /* TOKEN_DECREMENT  */
    TOKEN_BITWISE_AND = 306,       /* TOKEN_BITWISE_AND  */
    TOKEN_BITWISE_OR = 307,        /* TOKEN_BITWISE_OR  */
    TOKEN_LOGICAL_AND = 308,       /* TOKEN_LOGICAL_AND  */
    TOKEN_BITWISE_NOT = 309,       /* TOKEN_BITWISE_NOT  */
    TOKEN_BITWISE_XOR = 310,       /* TOKEN_BITWISE_XOR  */
    TOKEN_LOGICAL_NOT = 311,       /* TOKEN_LOGICAL_NOT  */
    TOKEN_LOGICAL_OR = 312,        /* TOKEN_LOGICAL_OR  */
    TOKEN_EQUAL = 313,             /* TOKEN_EQUAL  */
    TOKEN_NOT_EQUAL = 314,         /* TOKEN_NOT_EQUAL  */
    TOKEN_LESS_THAN = 315,         /* TOKEN_LESS_THAN  */
    TOKEN_GREATER_THAN = 316,      /* TOKEN_GREATER_THAN  */
    TOKEN_LESS_THAN_OR_EQUAL = 317, /* TOKEN_LESS_THAN_OR_EQUAL  */
    TOKEN_GREATER_THAN_OR_EQUAL = 318, /* TOKEN_GREATER_THAN_OR_EQUAL  */
    TOKEN_RIGHT_SHIFT = 319,       /* TOKEN_RIGHT_SHIFT  */
    TOKEN_LEFT_SHIFT = 320,        /* TOKEN_LEFT_SHIFT  */
    TOKEN_PLUS_ASSIGN = 321,       /* TOKEN_PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN = 322,      /* TOKEN_MINUS_ASSIGN  */
    TOKEN_LEFT_SHIFT_ASSIGN = 323, /* TOKEN_LEFT_SHIFT_ASSIGN  */
    TOKEN_RIGHT_SHIFT_ASSIGN = 324, /* TOKEN_RIGHT_SHIFT_ASSIGN  */
    TOKEN_BITWISE_AND_ASSIGN = 325, /* TOKEN_BITWISE_AND_ASSIGN  */
    TOKEN_BITWISE_OR_ASSIGN = 326, /* TOKEN_BITWISE_OR_ASSIGN  */
    TOKEN_BITWISE_XOR_ASSIGN = 327, /* TOKEN_BITWISE_XOR_ASSIGN  */
    TOKEN_MULTIPLY_ASSIGN = 328,   /* TOKEN_MULTIPLY_ASSIGN  */
    TOKEN_DIVIDE_ASSIGN = 329,     /* TOKEN_DIVIDE_ASSIGN  */
    TOKEN_MODULUS_ASSIGN = 330,    /* TOKEN_MODULUS_ASSIGN  */
    TOKEN_ARROW = 331,             /* TOKEN_ARROW  */
    TOKEN_CONSTANT = 332,          /* TOKEN_CONSTANT  */
    TOKEN_ASTERISK = 333,          /* TOKEN_ASTERISK  */
    TOKEN_ADDRESS_OF = 334,        /* TOKEN_ADDRESS_OF  */
    TOKEN_DOT = 335,               /* TOKEN_DOT  */
    TOKEN_FNUM = 336,              /* TOKEN_FNUM  */
    TOKEN_NUM = 337,               /* TOKEN_NUM  */
    TOKEN_STR = 338,               /* TOKEN_STR  */
    TOKEN_ID = 339,                /* TOKEN_ID  */
    TOKEN_CNUM = 340               /* TOKEN_CNUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef ParserObject_ut YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

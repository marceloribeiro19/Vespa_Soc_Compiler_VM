/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 15 "Parser/Parser.y"

#include <stdint.h>
#include <errno.h>
#include "../main.h"
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

int yylex();
int yyerror(char* pStr);
const char* getTokenName(int tokenValue);
TreeNode_st* pTreeRoot;
static char* currentFunction;



#line 89 "Parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_IF = 3,                   /* TOKEN_IF  */
  YYSYMBOL_TOKEN_EOF = 4,                  /* TOKEN_EOF  */
  YYSYMBOL_TOKEN_ERROR = 5,                /* TOKEN_ERROR  */
  YYSYMBOL_TOKEN_ELSE = 6,                 /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_DO = 7,                   /* TOKEN_DO  */
  YYSYMBOL_TOKEN_WHILE = 8,                /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_FOR = 9,                  /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_SWITCH = 10,              /* TOKEN_SWITCH  */
  YYSYMBOL_TOKEN_CASE = 11,                /* TOKEN_CASE  */
  YYSYMBOL_TOKEN_DEFAULT = 12,             /* TOKEN_DEFAULT  */
  YYSYMBOL_TOKEN_RETURN = 13,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_BREAK = 14,               /* TOKEN_BREAK  */
  YYSYMBOL_TOKEN_INT = 15,                 /* TOKEN_INT  */
  YYSYMBOL_TOKEN_FLOAT = 16,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_DOUBLE = 17,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_CHAR = 18,                /* TOKEN_CHAR  */
  YYSYMBOL_TOKEN_VOID = 19,                /* TOKEN_VOID  */
  YYSYMBOL_TOKEN_STRUCT = 20,              /* TOKEN_STRUCT  */
  YYSYMBOL_TOKEN_TYPEDEF = 21,             /* TOKEN_TYPEDEF  */
  YYSYMBOL_TOKEN_CONTINUE = 22,            /* TOKEN_CONTINUE  */
  YYSYMBOL_TOKEN_EXTERN = 23,              /* TOKEN_EXTERN  */
  YYSYMBOL_TOKEN_GOTO = 24,                /* TOKEN_GOTO  */
  YYSYMBOL_TOKEN_LONG = 25,                /* TOKEN_LONG  */
  YYSYMBOL_TOKEN_ENUM = 26,                /* TOKEN_ENUM  */
  YYSYMBOL_TOKEN_SHORT = 27,               /* TOKEN_SHORT  */
  YYSYMBOL_TOKEN_SIZEOF = 28,              /* TOKEN_SIZEOF  */
  YYSYMBOL_TOKEN_STATIC = 29,              /* TOKEN_STATIC  */
  YYSYMBOL_TOKEN_SIGNED = 30,              /* TOKEN_SIGNED  */
  YYSYMBOL_TOKEN_UNION = 31,               /* TOKEN_UNION  */
  YYSYMBOL_TOKEN_UNSIGNED = 32,            /* TOKEN_UNSIGNED  */
  YYSYMBOL_TOKEN_VOLATILE = 33,            /* TOKEN_VOLATILE  */
  YYSYMBOL_TOKEN_ASSIGN = 34,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS = 35,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 36,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_OVER = 37,                /* TOKEN_OVER  */
  YYSYMBOL_TOKEN_PERCENT = 38,             /* TOKEN_PERCENT  */
  YYSYMBOL_TOKEN_LEFT_PARENTHESES = 39,    /* TOKEN_LEFT_PARENTHESES  */
  YYSYMBOL_TOKEN_RIGHT_PARENTHESES = 40,   /* TOKEN_RIGHT_PARENTHESES  */
  YYSYMBOL_TOKEN_LEFT_BRACE = 41,          /* TOKEN_LEFT_BRACE  */
  YYSYMBOL_TOKEN_RIGHT_BRACE = 42,         /* TOKEN_RIGHT_BRACE  */
  YYSYMBOL_TOKEN_LEFT_BRACKET = 43,        /* TOKEN_LEFT_BRACKET  */
  YYSYMBOL_TOKEN_RIGHT_BRACKET = 44,       /* TOKEN_RIGHT_BRACKET  */
  YYSYMBOL_TOKEN_TERNARY = 45,             /* TOKEN_TERNARY  */
  YYSYMBOL_TOKEN_SEMI = 46,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_COLON = 47,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_COMMA = 48,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_INCREMENT = 49,           /* TOKEN_INCREMENT  */
  YYSYMBOL_TOKEN_DECREMENT = 50,           /* TOKEN_DECREMENT  */
  YYSYMBOL_TOKEN_BITWISE_AND = 51,         /* TOKEN_BITWISE_AND  */
  YYSYMBOL_TOKEN_BITWISE_OR = 52,          /* TOKEN_BITWISE_OR  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 53,         /* TOKEN_LOGICAL_AND  */
  YYSYMBOL_TOKEN_BITWISE_NOT = 54,         /* TOKEN_BITWISE_NOT  */
  YYSYMBOL_TOKEN_BITWISE_XOR = 55,         /* TOKEN_BITWISE_XOR  */
  YYSYMBOL_TOKEN_LOGICAL_NOT = 56,         /* TOKEN_LOGICAL_NOT  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 57,          /* TOKEN_LOGICAL_OR  */
  YYSYMBOL_TOKEN_EQUAL = 58,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_NOT_EQUAL = 59,           /* TOKEN_NOT_EQUAL  */
  YYSYMBOL_TOKEN_LESS_THAN = 60,           /* TOKEN_LESS_THAN  */
  YYSYMBOL_TOKEN_GREATER_THAN = 61,        /* TOKEN_GREATER_THAN  */
  YYSYMBOL_TOKEN_LESS_THAN_OR_EQUAL = 62,  /* TOKEN_LESS_THAN_OR_EQUAL  */
  YYSYMBOL_TOKEN_GREATER_THAN_OR_EQUAL = 63, /* TOKEN_GREATER_THAN_OR_EQUAL  */
  YYSYMBOL_TOKEN_RIGHT_SHIFT = 64,         /* TOKEN_RIGHT_SHIFT  */
  YYSYMBOL_TOKEN_LEFT_SHIFT = 65,          /* TOKEN_LEFT_SHIFT  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 66,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 67,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_LEFT_SHIFT_ASSIGN = 68,   /* TOKEN_LEFT_SHIFT_ASSIGN  */
  YYSYMBOL_TOKEN_RIGHT_SHIFT_ASSIGN = 69,  /* TOKEN_RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_AND_ASSIGN = 70,  /* TOKEN_BITWISE_AND_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_OR_ASSIGN = 71,   /* TOKEN_BITWISE_OR_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_XOR_ASSIGN = 72,  /* TOKEN_BITWISE_XOR_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 73,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 74,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULUS_ASSIGN = 75,      /* TOKEN_MODULUS_ASSIGN  */
  YYSYMBOL_TOKEN_ARROW = 76,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_CONSTANT = 77,            /* TOKEN_CONSTANT  */
  YYSYMBOL_TOKEN_ASTERISK = 78,            /* TOKEN_ASTERISK  */
  YYSYMBOL_TOKEN_ADDRESS_OF = 79,          /* TOKEN_ADDRESS_OF  */
  YYSYMBOL_TOKEN_DOT = 80,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_FNUM = 81,                /* TOKEN_FNUM  */
  YYSYMBOL_TOKEN_NUM = 82,                 /* TOKEN_NUM  */
  YYSYMBOL_TOKEN_STR = 83,                 /* TOKEN_STR  */
  YYSYMBOL_TOKEN_ID = 84,                  /* TOKEN_ID  */
  YYSYMBOL_TOKEN_CNUM = 85,                /* TOKEN_CNUM  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_R_PROGRAM = 87,                 /* R_PROGRAM  */
  YYSYMBOL_R_GLOBAL_STATEMENT = 88,        /* R_GLOBAL_STATEMENT  */
  YYSYMBOL_R_LOCAL_STATEMENT_LIST = 89,    /* R_LOCAL_STATEMENT_LIST  */
  YYSYMBOL_R_LOCAL_STATEMENT = 90,         /* R_LOCAL_STATEMENT  */
  YYSYMBOL_R_COMPOUND_STATEMENT = 91,      /* R_COMPOUND_STATEMENT  */
  YYSYMBOL_R_CONTINUE = 92,                /* R_CONTINUE  */
  YYSYMBOL_R_BREAK = 93,                   /* R_BREAK  */
  YYSYMBOL_R_GOTO = 94,                    /* R_GOTO  */
  YYSYMBOL_R_SWITCH = 95,                  /* R_SWITCH  */
  YYSYMBOL_R_SWITCH_BODY = 96,             /* R_SWITCH_BODY  */
  YYSYMBOL_R_CASE_LIST = 97,               /* R_CASE_LIST  */
  YYSYMBOL_R_CASE = 98,                    /* R_CASE  */
  YYSYMBOL_R_DEFAULT = 99,                 /* R_DEFAULT  */
  YYSYMBOL_R_IF_STATEMENT = 100,           /* R_IF_STATEMENT  */
  YYSYMBOL_R_RETURN = 101,                 /* R_RETURN  */
  YYSYMBOL_R_WHILE_LOOP = 102,             /* R_WHILE_LOOP  */
  YYSYMBOL_R_DO_WHILE_LOOP = 103,          /* R_DO_WHILE_LOOP  */
  YYSYMBOL_R_FOR_LOOP = 104,               /* R_FOR_LOOP  */
  YYSYMBOL_R_FOR_INIT_FIELD = 105,         /* R_FOR_INIT_FIELD  */
  YYSYMBOL_R_FOR_ASSIGNMENT_FIELD = 106,   /* R_FOR_ASSIGNMENT_FIELD  */
  YYSYMBOL_R_LABEL = 107,                  /* R_LABEL  */
  YYSYMBOL_R_FUNC_SIGNATURE = 108,         /* R_FUNC_SIGNATURE  */
  YYSYMBOL_R_FUNC_PROTOTYPE = 109,         /* R_FUNC_PROTOTYPE  */
  YYSYMBOL_R_FUNC_IMPLEMENT = 110,         /* R_FUNC_IMPLEMENT  */
  YYSYMBOL_R_FUNC_CALL = 111,              /* R_FUNC_CALL  */
  YYSYMBOL_R_EXP_LIST = 112,               /* R_EXP_LIST  */
  YYSYMBOL_R_ARG_LIST = 113,               /* R_ARG_LIST  */
  YYSYMBOL_R_ARG = 114,                    /* R_ARG  */
  YYSYMBOL_R_VAR_DECLARATION = 115,        /* R_VAR_DECLARATION  */
  YYSYMBOL_R_ARR_DECLARATION = 116,        /* R_ARR_DECLARATION  */
  YYSYMBOL_R_ARR_SIZE = 117,               /* R_ARR_SIZE  */
  YYSYMBOL_R_ID_LIST = 118,                /* R_ID_LIST  */
  YYSYMBOL_R_VAR_ASSIGNMENT = 119,         /* R_VAR_ASSIGNMENT  */
  YYSYMBOL_R_COMPOUND_VAR_ASSIGN = 120,    /* R_COMPOUND_VAR_ASSIGN  */
  YYSYMBOL_R_SIMPLE_VAR_ASSIGN = 121,      /* R_SIMPLE_VAR_ASSIGN  */
  YYSYMBOL_R_VAR_PREAMBLE = 122,           /* R_VAR_PREAMBLE  */
  YYSYMBOL_R_EXP = 123,                    /* R_EXP  */
  YYSYMBOL_R_TERM = 124,                   /* R_TERM  */
  YYSYMBOL_R_OPERAND = 125,                /* R_OPERAND  */
  YYSYMBOL_R_FACTOR = 126,                 /* R_FACTOR  */
  YYSYMBOL_R_ARRAY_INDEX = 127,            /* R_ARRAY_INDEX  */
  YYSYMBOL_R_POINTER_CONTENT = 128,        /* R_POINTER_CONTENT  */
  YYSYMBOL_R_INC_DEC = 129,                /* R_INC_DEC  */
  YYSYMBOL_R_PRE_INCREMENT = 130,          /* R_PRE_INCREMENT  */
  YYSYMBOL_R_POST_INCREMENT = 131,         /* R_POST_INCREMENT  */
  YYSYMBOL_R_PRE_DECREMENT = 132,          /* R_PRE_DECREMENT  */
  YYSYMBOL_R_POST_DECREMENT = 133,         /* R_POST_DECREMENT  */
  YYSYMBOL_R_ARITHMETIC_OPERATOR = 134,    /* R_ARITHMETIC_OPERATOR  */
  YYSYMBOL_R_PRIORITY_OPERATOR = 135,      /* R_PRIORITY_OPERATOR  */
  YYSYMBOL_R_CONDITION_OPERATOR = 136,     /* R_CONDITION_OPERATOR  */
  YYSYMBOL_R_LOGIC_OPERATOR = 137,         /* R_LOGIC_OPERATOR  */
  YYSYMBOL_R_BITWISE_OPERATOR = 138,       /* R_BITWISE_OPERATOR  */
  YYSYMBOL_R_COMPOUND_ASSIGN_OPERATOR = 139, /* R_COMPOUND_ASSIGN_OPERATOR  */
  YYSYMBOL_R_TYPE_CAST = 140,              /* R_TYPE_CAST  */
  YYSYMBOL_R_TYPE_ALL = 141,               /* R_TYPE_ALL  */
  YYSYMBOL_R_TYPE_PTR = 142,               /* R_TYPE_PTR  */
  YYSYMBOL_R_TYPE = 143,                   /* R_TYPE  */
  YYSYMBOL_R_VISIBILITY_QUALIFIER = 144,   /* R_VISIBILITY_QUALIFIER  */
  YYSYMBOL_R_MOD_QUALIFIER = 145,          /* R_MOD_QUALIFIER  */
  YYSYMBOL_R_SIGN_QUALIFIER = 146          /* R_SIGN_QUALIFIER  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1061

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  285

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   340


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   137,   156,   163,   168,   173,   181,   186,
     205,   212,   217,   222,   227,   232,   237,   242,   247,   252,
     257,   262,   267,   272,   277,   282,   290,   317,   329,   335,
     341,   350,   359,   378,   383,   391,   410,   418,   425,   436,
     447,   455,   467,   473,   486,   495,   503,   512,   540,   555,
     560,   565,   576,   588,   602,   609,   617,   627,   632,   652,
     660,   665,   684,   691,   702,   712,   722,   737,   758,   768,
     779,   788,   813,   843,   854,   865,   870,   875,   884,   895,
     909,   926,   934,   941,   948,   955,   961,   967,   973,   983,
     991,   999,  1007,  1015,  1022,  1030,  1039,  1048,  1056,  1063,
    1068,  1076,  1082,  1091,  1096,  1101,  1107,  1113,  1119,  1124,
    1130,  1136,  1142,  1148,  1155,  1161,  1168,  1178,  1187,  1192,
    1197,  1202,  1210,  1218,  1226,  1234,  1247,  1253,  1259,  1265,
    1273,  1279,  1285,  1293,  1299,  1305,  1311,  1317,  1323,  1331,
    1337,  1345,  1351,  1357,  1365,  1371,  1377,  1383,  1389,  1395,
    1401,  1407,  1413,  1419,  1432,  1441,  1446,  1454,  1465,  1471,
    1477,  1483,  1489,  1495,  1501,  1506,  1515,  1521,  1531,  1537,
    1545,  1551
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_IF",
  "TOKEN_EOF", "TOKEN_ERROR", "TOKEN_ELSE", "TOKEN_DO", "TOKEN_WHILE",
  "TOKEN_FOR", "TOKEN_SWITCH", "TOKEN_CASE", "TOKEN_DEFAULT",
  "TOKEN_RETURN", "TOKEN_BREAK", "TOKEN_INT", "TOKEN_FLOAT",
  "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_VOID", "TOKEN_STRUCT",
  "TOKEN_TYPEDEF", "TOKEN_CONTINUE", "TOKEN_EXTERN", "TOKEN_GOTO",
  "TOKEN_LONG", "TOKEN_ENUM", "TOKEN_SHORT", "TOKEN_SIZEOF",
  "TOKEN_STATIC", "TOKEN_SIGNED", "TOKEN_UNION", "TOKEN_UNSIGNED",
  "TOKEN_VOLATILE", "TOKEN_ASSIGN", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_OVER", "TOKEN_PERCENT", "TOKEN_LEFT_PARENTHESES",
  "TOKEN_RIGHT_PARENTHESES", "TOKEN_LEFT_BRACE", "TOKEN_RIGHT_BRACE",
  "TOKEN_LEFT_BRACKET", "TOKEN_RIGHT_BRACKET", "TOKEN_TERNARY",
  "TOKEN_SEMI", "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_INCREMENT",
  "TOKEN_DECREMENT", "TOKEN_BITWISE_AND", "TOKEN_BITWISE_OR",
  "TOKEN_LOGICAL_AND", "TOKEN_BITWISE_NOT", "TOKEN_BITWISE_XOR",
  "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR", "TOKEN_EQUAL",
  "TOKEN_NOT_EQUAL", "TOKEN_LESS_THAN", "TOKEN_GREATER_THAN",
  "TOKEN_LESS_THAN_OR_EQUAL", "TOKEN_GREATER_THAN_OR_EQUAL",
  "TOKEN_RIGHT_SHIFT", "TOKEN_LEFT_SHIFT", "TOKEN_PLUS_ASSIGN",
  "TOKEN_MINUS_ASSIGN", "TOKEN_LEFT_SHIFT_ASSIGN",
  "TOKEN_RIGHT_SHIFT_ASSIGN", "TOKEN_BITWISE_AND_ASSIGN",
  "TOKEN_BITWISE_OR_ASSIGN", "TOKEN_BITWISE_XOR_ASSIGN",
  "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULUS_ASSIGN",
  "TOKEN_ARROW", "TOKEN_CONSTANT", "TOKEN_ASTERISK", "TOKEN_ADDRESS_OF",
  "TOKEN_DOT", "TOKEN_FNUM", "TOKEN_NUM", "TOKEN_STR", "TOKEN_ID",
  "TOKEN_CNUM", "$accept", "R_PROGRAM", "R_GLOBAL_STATEMENT",
  "R_LOCAL_STATEMENT_LIST", "R_LOCAL_STATEMENT", "R_COMPOUND_STATEMENT",
  "R_CONTINUE", "R_BREAK", "R_GOTO", "R_SWITCH", "R_SWITCH_BODY",
  "R_CASE_LIST", "R_CASE", "R_DEFAULT", "R_IF_STATEMENT", "R_RETURN",
  "R_WHILE_LOOP", "R_DO_WHILE_LOOP", "R_FOR_LOOP", "R_FOR_INIT_FIELD",
  "R_FOR_ASSIGNMENT_FIELD", "R_LABEL", "R_FUNC_SIGNATURE",
  "R_FUNC_PROTOTYPE", "R_FUNC_IMPLEMENT", "R_FUNC_CALL", "R_EXP_LIST",
  "R_ARG_LIST", "R_ARG", "R_VAR_DECLARATION", "R_ARR_DECLARATION",
  "R_ARR_SIZE", "R_ID_LIST", "R_VAR_ASSIGNMENT", "R_COMPOUND_VAR_ASSIGN",
  "R_SIMPLE_VAR_ASSIGN", "R_VAR_PREAMBLE", "R_EXP", "R_TERM", "R_OPERAND",
  "R_FACTOR", "R_ARRAY_INDEX", "R_POINTER_CONTENT", "R_INC_DEC",
  "R_PRE_INCREMENT", "R_POST_INCREMENT", "R_PRE_DECREMENT",
  "R_POST_DECREMENT", "R_ARITHMETIC_OPERATOR", "R_PRIORITY_OPERATOR",
  "R_CONDITION_OPERATOR", "R_LOGIC_OPERATOR", "R_BITWISE_OPERATOR",
  "R_COMPOUND_ASSIGN_OPERATOR", "R_TYPE_CAST", "R_TYPE_ALL", "R_TYPE_PTR",
  "R_TYPE", "R_VISIBILITY_QUALIFIER", "R_MOD_QUALIFIER",
  "R_SIGN_QUALIFIER", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     380,  -178,  -178,  -178,  -178,  -178,  -178,    27,  -178,  -178,
    -178,  -178,  -178,  -178,    89,  -178,     0,  -178,  -178,  -178,
    -178,   -17,  -178,  -178,    -5,   466,  1029,    69,  -178,  -178,
    -178,  -178,   135,  -178,  -178,    -3,    20,  -178,  -178,  -178,
    1029,    69,  -178,    69,  -178,    36,   501,    38,    70,    71,
     265,    65,    67,    31,  -178,    33,    39,    40,   565,   351,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,    74,  -178,  -178,    80,    81,    41,    94,    95,
      84,  -178,  -178,  -178,  -178,   505,   466,    49,    88,  -178,
      51,  -178,    69,  -178,  -178,   505,   128,   505,    53,   505,
     513,   256,  -178,    55,    -2,   382,  -178,  -178,  -178,    12,
    -178,  -178,   616,   -28,  -178,  -178,  -178,  -178,  -178,   382,
    -178,  -178,   100,  -178,  -178,  -178,   505,   505,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   505,  -178,  -178,  -178,  -178,  -178,    -1,   505,   505,
    -178,   957,     5,  -178,    56,  1029,    69,   103,  -178,   121,
    -178,  -178,   647,   117,   678,   127,   123,   709,  -178,  -178,
     978,   740,   130,   120,  -178,   -22,   -28,   505,   -11,  -178,
    -178,  -178,   505,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,    -2,    -2,    -2,
      -2,  -178,  -178,  -178,    -2,  -178,  -178,    16,   957,   771,
     957,   802,   833,  -178,   466,  -178,    87,    69,    90,  -178,
     501,   505,   429,   505,   505,   131,  -178,  -178,  -178,  -178,
     864,   -28,   -28,   -28,   -28,  -178,  -178,   505,  -178,  -178,
    -178,  -178,  -178,    91,  -178,   167,   895,  -178,  -178,   957,
     926,    79,   505,   957,  -178,   501,   132,   -26,    10,   134,
     137,    79,  -178,  -178,   957,  -178,  -178,   575,   143,  -178,
    -178,  -178,   139,   140,   501,  -178,  -178,  -178,   501,   501,
     501,   501,  -178,   501,   501
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   160,   162,   163,   158,   165,   167,   161,   159,   166,
     170,   171,   169,   168,     0,     4,     0,     6,     7,     5,
      68,     0,    88,   156,   155,     0,     0,     0,   164,     1,
       2,     3,     0,    54,    55,    74,     0,    73,   157,    85,
       0,     0,    86,     0,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
      10,    20,    15,    14,    12,    13,    11,    21,    18,    16,
      19,    17,     0,    22,    23,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,     0,    60,     0,     0,    67,
       0,    82,     0,    83,    84,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,   110,   106,   112,   107,
     111,   115,     0,    96,    98,   102,   104,   108,    99,     0,
      29,    28,     0,   122,   124,   117,    57,     0,    52,   123,
     125,   144,   145,   147,   148,   149,   150,   151,   152,   153,
     146,     0,    26,     9,    24,    76,    75,    74,     0,     0,
      25,    80,     0,    62,     0,     0,     0,     0,    69,    71,
      72,    81,     0,     0,     0,     0,     0,     0,   109,   105,
      89,     0,     0,   114,   113,     0,    93,     0,   107,   100,
     126,   127,     0,    43,   141,   142,   139,   143,   140,   137,
     138,   136,   133,   134,   135,   128,   129,     0,     0,     0,
       0,   131,   132,   130,     0,   101,    30,     0,    59,     0,
      79,     0,     0,    53,     0,    66,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,   103,   154,   109,   105,
       0,    90,    91,    94,    92,    97,    56,     0,   116,    77,
      78,    61,    65,     0,    64,    40,     0,    45,    44,    48,
       0,     0,     0,    58,    63,     0,     0,     0,     0,     0,
       0,    33,    36,    34,    95,    41,    46,     0,     0,    50,
      49,    51,     0,     0,     8,    31,    35,    32,     0,     8,
       8,    39,    47,    37,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,   175,  -177,   -40,   176,  -178,  -178,  -178,  -178,
    -178,  -178,   -68,   -66,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,   -16,  -178,  -178,   -15,     7,
    -178,  -178,  -178,  -178,   -60,   -20,    15,   203,   -99,     1,
     -80,   -32,     6,   -24,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,   -23,  -178,  -178,  -178,   -12,
     -14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    14,    15,    59,    60,    61,    62,    63,    64,    65,
     260,   261,   262,   263,    66,    67,    68,    69,    70,   166,
     268,    71,    16,    17,    18,   111,   207,   152,   153,    73,
      20,    88,    36,    74,    75,    76,    77,   171,   113,   114,
     115,   116,   117,   118,    81,    82,    83,    84,   197,   204,
     198,   199,   200,   141,   119,    22,    23,    24,    25,    26,
      27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    37,    39,    42,    44,   176,    96,    19,    80,   201,
     202,    41,    43,    40,    78,    21,    72,    91,    93,   143,
      94,    19,    80,    55,    56,   179,    92,    78,   126,    21,
      72,    85,   127,    85,   175,    80,    86,   101,    79,   205,
      87,    32,    87,    72,    28,   213,    33,    55,    56,   103,
     203,   126,    79,   214,   105,   127,   236,    37,   267,   228,
     229,   129,   130,   154,   237,    79,    89,    35,    90,   161,
     160,   174,   156,    38,   155,    95,    57,    97,   172,   106,
     107,   108,   109,   110,     1,     2,     3,     4,     5,    29,
     258,   259,   272,    30,     7,   273,     8,   281,   231,   232,
     233,   234,   283,   284,     1,     2,     3,     4,     5,    98,
      99,   120,     6,   121,     7,   122,     8,   123,     9,    10,
     144,    11,    12,   124,   125,   147,   145,   146,   148,   149,
     150,   157,   216,   218,   158,   159,   163,   165,    45,   173,
     215,   217,    46,    47,    48,    49,   206,   219,    50,    51,
       1,     2,     3,     4,     5,    85,   221,    52,     6,    53,
       7,   223,     8,   127,     9,    10,    13,    11,    12,   224,
     227,   242,   251,   255,   244,   254,    32,    54,   266,   275,
     245,   274,   248,   278,    55,    56,   279,   280,    78,    31,
      78,   154,    34,   276,   243,   277,    80,   269,    80,   241,
     156,     0,   155,     0,    72,   235,    72,     0,     0,     0,
       0,     0,    13,    57,     0,   265,     0,     0,     0,    58,
       0,     0,     0,    78,     0,     0,    79,     0,    79,     0,
       0,    80,     0,   271,     0,     0,     0,   270,   282,    72,
       0,   143,    78,   143,   143,     0,    78,    78,    78,    78,
      80,    78,    78,   112,    80,    80,    80,    80,    72,    80,
      80,    79,    72,    72,    72,    72,     0,    72,    72,     0,
       0,     1,     2,     3,     4,     5,     0,     0,     0,     0,
      79,     7,     0,     8,    79,    79,    79,    79,   151,    79,
      79,     0,   100,     0,     0,   101,     0,     0,   162,     0,
     164,   100,   167,   170,   101,    55,    56,   103,     0,     0,
     104,   102,   105,     0,    55,    56,   103,     0,     0,   104,
       0,   105,     0,     0,     0,     0,     0,     0,     0,   208,
     209,     0,     0,     0,    57,     0,     0,   106,   107,   108,
     109,   110,     0,    57,   210,     0,   106,   107,   108,   109,
     110,   211,   212,     0,    45,     0,     0,     0,    46,    47,
      48,    49,     0,     0,    50,    51,     1,     2,     3,     4,
       5,     0,     0,    52,     6,    53,     7,     0,     8,     0,
       9,    10,     0,    11,    12,   230,     0,     0,     0,     0,
       0,     0,    32,   142,     0,     1,     2,     3,     4,     5,
      55,    56,     0,     6,     0,     7,     0,     8,     0,     9,
      10,     0,    11,    12,     0,     0,     0,     0,   175,     0,
       0,   177,     0,     0,   246,     0,   249,   250,    13,    57,
       0,     0,    45,   103,     0,    58,    46,    47,    48,    49,
     253,     0,    50,    51,     1,     2,     3,     4,     5,     0,
       0,    52,     6,    53,     7,   264,     8,    13,     9,    10,
      57,    11,    12,   106,   107,   108,   178,   110,     0,     0,
      32,     0,     0,     0,     0,   247,     0,     0,    55,    56,
       0,     1,     2,     3,     4,     5,     0,     0,     0,     0,
       0,     7,     0,     8,     0,     0,    10,     0,    11,    12,
       0,     0,     0,     0,    45,     0,    13,    57,    46,    47,
      48,    49,     0,    58,    50,    51,     1,     2,     3,     4,
       5,     0,     0,    52,     6,    53,     7,     0,     8,     0,
       9,    10,     0,    11,    12,     0,     0,     0,     0,     0,
       0,   100,    32,    13,   101,     0,     0,     0,     0,   100,
      55,    56,   101,     0,    55,    56,   103,     0,     0,   104,
       0,   105,    55,    56,   103,     0,     0,   104,     0,   105,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    57,
       0,     0,     0,    57,     0,    58,   106,   107,   108,   109,
     110,    57,     0,     0,   168,   169,   108,   109,   110,    85,
       0,     0,     0,     0,   126,     0,     0,     0,   127,    85,
       0,     0,   128,     0,   129,   130,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,     0,     0,     0,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,     0,     0,     0,     0,   184,   185,   186,
       0,   187,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   180,   181,     0,     0,     0,   220,     0,     0,
       0,     0,   182,     0,     0,     0,     0,     0,   184,   185,
     186,     0,   187,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   180,   181,     0,     0,     0,   222,     0,
       0,     0,     0,   182,     0,     0,     0,     0,     0,   184,
     185,   186,     0,   187,     0,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   180,   181,     0,     0,     0,   225,
       0,     0,     0,     0,   182,     0,     0,     0,     0,     0,
     184,   185,   186,     0,   187,     0,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   180,   181,     0,     0,     0,
     226,     0,     0,     0,     0,   182,     0,     0,     0,     0,
       0,   184,   185,   186,     0,   187,     0,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   180,   181,     0,     0,
       0,     0,     0,     0,     0,   238,   182,     0,     0,     0,
       0,     0,   184,   185,   186,     0,   187,     0,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   239,     0,
       0,     0,     0,   184,   185,   186,     0,   187,     0,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   240,
       0,     0,     0,     0,   184,   185,   186,     0,   187,     0,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,   182,
       0,   252,     0,     0,     0,   184,   185,   186,     0,   187,
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     180,   181,     0,     0,     0,   256,     0,     0,     0,     0,
     182,     0,     0,     0,     0,     0,   184,   185,   186,     0,
     187,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   257,     0,     0,     0,     0,   184,   185,   186,
       0,   187,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,   182,     0,     0,     0,     0,     0,   184,   185,
     186,     0,   187,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   182,     0,     0,     0,     0,     0,   184,
     185,   186,     0,   187,     0,   188,   189,   190,   191,   192,
     193,   194,   195,   196,     1,     2,     3,     4,     5,     0,
       0,     0,     0,     0,     7,     0,     8,     0,     0,    10,
       0,    11
};

static const yytype_int16 yycheck[] =
{
      32,    21,    25,    26,    27,   104,    46,     0,    32,    37,
      38,    25,    26,    25,    46,     0,    32,    40,    41,    59,
      43,    14,    46,    49,    50,   105,    40,    59,    39,    14,
      46,    34,    43,    34,    36,    59,    39,    39,    32,   119,
      43,    41,    43,    59,    17,    40,    46,    49,    50,    51,
      78,    39,    46,    48,    56,    43,    40,    77,    84,    81,
      82,    49,    50,    86,    48,    59,    46,    84,    48,    92,
      90,   103,    86,    78,    86,    39,    78,    39,   101,    81,
      82,    83,    84,    85,    15,    16,    17,    18,    19,     0,
      11,    12,    82,     4,    25,    85,    27,   274,   197,   198,
     199,   200,   279,   280,    15,    16,    17,    18,    19,    39,
      39,    46,    23,    46,    25,    84,    27,    84,    29,    30,
      46,    32,    33,    84,    84,    84,    46,    46,    34,    34,
      46,    82,   155,   156,    46,    84,     8,    84,     3,    84,
      84,   155,     7,     8,     9,    10,    46,    44,    13,    14,
      15,    16,    17,    18,    19,    34,    39,    22,    23,    24,
      25,    34,    27,    43,    29,    30,    77,    32,    33,    46,
      40,    84,    41,     6,    84,    84,    41,    42,    46,    42,
     220,    47,   222,    40,    49,    50,    47,    47,   220,    14,
     222,   214,    16,   261,   217,   261,   220,   257,   222,   214,
     214,    -1,   214,    -1,   220,   204,   222,    -1,    -1,    -1,
      -1,    -1,    77,    78,    -1,   255,    -1,    -1,    -1,    84,
      -1,    -1,    -1,   255,    -1,    -1,   220,    -1,   222,    -1,
      -1,   255,    -1,   257,    -1,    -1,    -1,   257,   278,   255,
      -1,   281,   274,   283,   284,    -1,   278,   279,   280,   281,
     274,   283,   284,    50,   278,   279,   280,   281,   274,   283,
     284,   255,   278,   279,   280,   281,    -1,   283,   284,    -1,
      -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     274,    25,    -1,    27,   278,   279,   280,   281,    85,   283,
     284,    -1,    36,    -1,    -1,    39,    -1,    -1,    95,    -1,
      97,    36,    99,   100,    39,    49,    50,    51,    -1,    -1,
      54,    46,    56,    -1,    49,    50,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    78,    -1,    -1,    81,    82,    83,
      84,    85,    -1,    78,   141,    -1,    81,    82,    83,    84,
      85,   148,   149,    -1,     3,    -1,    -1,    -1,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    24,    25,    -1,    27,    -1,
      29,    30,    -1,    32,    33,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    15,    16,    17,    18,    19,
      49,    50,    -1,    23,    -1,    25,    -1,    27,    -1,    29,
      30,    -1,    32,    33,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    39,    -1,    -1,   221,    -1,   223,   224,    77,    78,
      -1,    -1,     3,    51,    -1,    84,     7,     8,     9,    10,
     237,    -1,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    23,    24,    25,   252,    27,    77,    29,    30,
      78,    32,    33,    81,    82,    83,    84,    85,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    30,    -1,    32,    33,
      -1,    -1,    -1,    -1,     3,    -1,    77,    78,     7,     8,
       9,    10,    -1,    84,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    24,    25,    -1,    27,    -1,
      29,    30,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    41,    77,    39,    -1,    -1,    -1,    -1,    36,
      49,    50,    39,    -1,    49,    50,    51,    -1,    -1,    54,
      -1,    56,    49,    50,    51,    -1,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      -1,    -1,    -1,    78,    -1,    84,    81,    82,    83,    84,
      85,    78,    -1,    -1,    81,    82,    83,    84,    85,    34,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    34,
      -1,    -1,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    35,    36,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      35,    36,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,
      55,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    30,
      -1,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    16,    17,    18,    19,    23,    25,    27,    29,
      30,    32,    33,    77,    87,    88,   108,   109,   110,   115,
     116,   122,   141,   142,   143,   144,   145,   146,    17,     0,
       4,    88,    41,    46,    91,    84,   118,   121,    78,   141,
     145,   146,   141,   146,   141,     3,     7,     8,     9,    10,
      13,    14,    22,    24,    42,    49,    50,    78,    84,    89,
      90,    91,    92,    93,    94,    95,   100,   101,   102,   103,
     104,   107,   111,   115,   119,   120,   121,   122,   127,   128,
     129,   130,   131,   132,   133,    34,    39,    43,   117,    46,
      48,   141,   146,   141,   141,    39,    90,    39,    39,    39,
      36,    39,    46,    51,    54,    56,    81,    82,    83,    84,
      85,   111,   123,   124,   125,   126,   127,   128,   129,   140,
      46,    46,    84,    84,    84,    84,    39,    43,    47,    49,
      50,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,   139,    42,    90,    46,    46,    46,    84,    34,    34,
      46,   123,   113,   114,   141,   145,   146,    82,    46,    84,
     121,   141,   123,     8,   123,    84,   105,   123,    81,    82,
     123,   123,   141,    84,   127,    36,   124,    39,    84,   126,
      35,    36,    45,    46,    51,    52,    53,    55,    57,    58,
      59,    60,    61,    62,    63,    64,    65,   134,   136,   137,
     138,    37,    38,    78,   135,   126,    46,   112,   123,   123,
     123,   123,   123,    40,    48,    84,   141,   146,   141,    44,
      40,    39,    40,    34,    46,    40,    40,    40,    81,    82,
     123,   124,   124,   124,   124,   125,    40,    48,    44,    46,
      46,   114,    84,   141,    84,    90,   123,    46,    90,   123,
     123,    41,    47,   123,    84,     6,    40,    46,    11,    12,
      96,    97,    98,    99,   123,    90,    46,    84,   106,   120,
     121,   129,    82,    85,    47,    42,    98,    99,    40,    47,
      47,    89,    90,    89,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    91,    92,    93,
      94,    95,    96,    96,    96,    97,    97,    98,    98,    99,
     100,   100,   101,   101,   102,   102,   103,   104,   105,   106,
     106,   106,   107,   108,   109,   110,   111,   112,   112,   112,
     113,   113,   113,   114,   114,   114,   114,   115,   115,   116,
     117,   118,   118,   118,   118,   119,   119,   119,   119,   120,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   128,   129,   129,
     129,   129,   130,   131,   132,   133,   134,   134,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   137,
     137,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   141,   141,   142,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   144,   145,   145,
     146,   146
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     2,     2,     2,
       3,     7,     2,     1,     1,     2,     1,     4,     4,     3,
       5,     7,     2,     3,     5,     5,     7,     9,     3,     1,
       1,     1,     2,     5,     2,     2,     4,     0,     3,     1,
       0,     3,     1,     4,     3,     3,     2,     3,     1,     4,
       3,     3,     3,     1,     1,     2,     2,     4,     4,     3,
       3,     4,     3,     3,     3,     2,     2,     2,     1,     2,
       3,     3,     3,     2,     3,     5,     1,     3,     1,     1,
       2,     2,     1,     3,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     2,     2,     1,     4,     2,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* R_PROGRAM: R_PROGRAM TOKEN_EOF  */
#line 132 "Parser/Parser.y"
                            {
                                pTreeRoot = yyvsp[-1].treeNode;
                                LOG_DEBUG("Reached end of file!\n");
                                return 0;
                            }
#line 1620 "Parser.tab.c"
    break;

  case 3: /* R_PROGRAM: R_PROGRAM R_GLOBAL_STATEMENT  */
#line 138 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                                pTreeRoot = yyval.treeNode;
                            }
#line 1643 "Parser.tab.c"
    break;

  case 4: /* R_PROGRAM: R_GLOBAL_STATEMENT  */
#line 157 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1651 "Parser.tab.c"
    break;

  case 5: /* R_GLOBAL_STATEMENT: R_VAR_DECLARATION  */
#line 164 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1659 "Parser.tab.c"
    break;

  case 6: /* R_GLOBAL_STATEMENT: R_FUNC_PROTOTYPE  */
#line 169 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1667 "Parser.tab.c"
    break;

  case 7: /* R_GLOBAL_STATEMENT: R_FUNC_IMPLEMENT  */
#line 174 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1675 "Parser.tab.c"
    break;

  case 8: /* R_LOCAL_STATEMENT_LIST: %empty  */
#line 182 "Parser/Parser.y"
                            {
                                yyval.treeNode = NULL;
                            }
#line 1683 "Parser.tab.c"
    break;

  case 9: /* R_LOCAL_STATEMENT_LIST: R_LOCAL_STATEMENT_LIST R_LOCAL_STATEMENT  */
#line 187 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                            }
#line 1705 "Parser.tab.c"
    break;

  case 10: /* R_LOCAL_STATEMENT_LIST: R_LOCAL_STATEMENT  */
#line 206 "Parser/Parser.y"
                            { 
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1713 "Parser.tab.c"
    break;

  case 11: /* R_LOCAL_STATEMENT: R_IF_STATEMENT  */
#line 213 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1721 "Parser.tab.c"
    break;

  case 12: /* R_LOCAL_STATEMENT: R_GOTO  */
#line 218 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1729 "Parser.tab.c"
    break;

  case 13: /* R_LOCAL_STATEMENT: R_SWITCH  */
#line 223 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1737 "Parser.tab.c"
    break;

  case 14: /* R_LOCAL_STATEMENT: R_BREAK  */
#line 228 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1745 "Parser.tab.c"
    break;

  case 15: /* R_LOCAL_STATEMENT: R_CONTINUE  */
#line 233 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1753 "Parser.tab.c"
    break;

  case 16: /* R_LOCAL_STATEMENT: R_DO_WHILE_LOOP  */
#line 238 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1761 "Parser.tab.c"
    break;

  case 17: /* R_LOCAL_STATEMENT: R_LABEL  */
#line 243 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1769 "Parser.tab.c"
    break;

  case 18: /* R_LOCAL_STATEMENT: R_WHILE_LOOP  */
#line 248 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1777 "Parser.tab.c"
    break;

  case 19: /* R_LOCAL_STATEMENT: R_FOR_LOOP  */
#line 253 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1785 "Parser.tab.c"
    break;

  case 20: /* R_LOCAL_STATEMENT: R_COMPOUND_STATEMENT  */
#line 258 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1793 "Parser.tab.c"
    break;

  case 21: /* R_LOCAL_STATEMENT: R_RETURN  */
#line 263 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1801 "Parser.tab.c"
    break;

  case 22: /* R_LOCAL_STATEMENT: R_VAR_DECLARATION  */
#line 268 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1809 "Parser.tab.c"
    break;

  case 23: /* R_LOCAL_STATEMENT: R_VAR_ASSIGNMENT  */
#line 273 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1817 "Parser.tab.c"
    break;

  case 24: /* R_LOCAL_STATEMENT: R_FUNC_CALL TOKEN_SEMI  */
#line 278 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 1825 "Parser.tab.c"
    break;

  case 25: /* R_LOCAL_STATEMENT: R_INC_DEC TOKEN_SEMI  */
#line 283 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 1833 "Parser.tab.c"
    break;

  case 26: /* R_COMPOUND_STATEMENT: TOKEN_LEFT_BRACE R_LOCAL_STATEMENT_LIST TOKEN_RIGHT_BRACE  */
#line 291 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;
                                TreeNode_st* pEnd;
                                TreeNode_st* pStart;
                                TreeNode_st* pNull;

                                if (pNode != NULL)
                                { 
                                    NodeCreate(&pEnd, NODE_END_SCOPE);
                                    NodeCreate(&pStart, NODE_START_SCOPE);

                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = pEnd;
                                    yyval.treeNode = pStart;
                                    pStart->pSibling = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    NodeCreate(&pNull, NODE_NULL);
                                    yyval.treeNode = pNull;
                                }
                            }
#line 1863 "Parser.tab.c"
    break;

  case 27: /* R_COMPOUND_STATEMENT: TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE  */
#line 318 "Parser/Parser.y"
                            {
                                yyval.treeNode = NULL;
                            }
#line 1871 "Parser.tab.c"
    break;

  case 28: /* R_CONTINUE: TOKEN_CONTINUE TOKEN_SEMI  */
#line 330 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_CONTINUE);
                }
#line 1879 "Parser.tab.c"
    break;

  case 29: /* R_BREAK: TOKEN_BREAK TOKEN_SEMI  */
#line 336 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_BREAK);
                }
#line 1887 "Parser.tab.c"
    break;

  case 30: /* R_GOTO: TOKEN_GOTO TOKEN_ID TOKEN_SEMI  */
#line 342 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_GOTO);
                    yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                }
#line 1896 "Parser.tab.c"
    break;

  case 31: /* R_SWITCH: TOKEN_SWITCH TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_LEFT_BRACE R_SWITCH_BODY TOKEN_RIGHT_BRACE  */
#line 351 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_SWITCH);
                    NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);
                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                }
#line 1906 "Parser.tab.c"
    break;

  case 32: /* R_SWITCH_BODY: R_CASE_LIST R_DEFAULT  */
#line 360 "Parser/Parser.y"
                    {
                        TreeNode_st* pNode = yyvsp[-1].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = yyvsp[0].treeNode;
                            yyval.treeNode = yyvsp[-1].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = yyvsp[0].treeNode;
                        }
                    }
#line 1928 "Parser.tab.c"
    break;

  case 33: /* R_SWITCH_BODY: R_CASE_LIST  */
#line 379 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1936 "Parser.tab.c"
    break;

  case 34: /* R_SWITCH_BODY: R_DEFAULT  */
#line 384 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1944 "Parser.tab.c"
    break;

  case 35: /* R_CASE_LIST: R_CASE_LIST R_CASE  */
#line 392 "Parser/Parser.y"
                    {
                        TreeNode_st* pNode = yyvsp[-1].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = yyvsp[0].treeNode;
                            yyval.treeNode = yyvsp[-1].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = yyvsp[0].treeNode;
                        }
                    }
#line 1966 "Parser.tab.c"
    break;

  case 36: /* R_CASE_LIST: R_CASE  */
#line 411 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1974 "Parser.tab.c"
    break;

  case 37: /* R_CASE: TOKEN_CASE TOKEN_NUM TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 419 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_CASE);
                        yyval.treeNode->nodeData.dVal = yyvsp[-2].nodeData.dVal;

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 1985 "Parser.tab.c"
    break;

  case 38: /* R_CASE: TOKEN_CASE TOKEN_CNUM TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 426 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_CASE);
                        yyval.treeNode->nodeData.dVal = yyvsp[-2].nodeData.dVal;

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 1996 "Parser.tab.c"
    break;

  case 39: /* R_DEFAULT: TOKEN_DEFAULT TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 437 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_DEFAULT);

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 2006 "Parser.tab.c"
    break;

  case 40: /* R_IF_STATEMENT: TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT  */
#line 448 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_IF);

                        NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);                      // Condition:
                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);                      // if true
                    }
#line 2017 "Parser.tab.c"
    break;

  case 41: /* R_IF_STATEMENT: TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT TOKEN_ELSE R_LOCAL_STATEMENT  */
#line 456 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_IF);

                        NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);                      // Condition:
                        NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);                      // if true
                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);                      // else 
                    }
#line 2029 "Parser.tab.c"
    break;

  case 42: /* R_RETURN: TOKEN_RETURN TOKEN_SEMI  */
#line 468 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_RETURN);
                        yyval.treeNode->nodeData.sVal = currentFunction;
                    }
#line 2038 "Parser.tab.c"
    break;

  case 43: /* R_RETURN: TOKEN_RETURN R_EXP TOKEN_SEMI  */
#line 474 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_RETURN);
                        NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        yyval.treeNode->nodeData.sVal = currentFunction;
                    }
#line 2048 "Parser.tab.c"
    break;

  case 44: /* R_WHILE_LOOP: TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT  */
#line 487 "Parser/Parser.y"
                        {

                            NodeCreate(&(yyval.treeNode), NODE_WHILE);
                        
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);      // if true
                        }
#line 2060 "Parser.tab.c"
    break;

  case 45: /* R_WHILE_LOOP: TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI  */
#line 496 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_WHILE);
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                        }
#line 2069 "Parser.tab.c"
    break;

  case 46: /* R_DO_WHILE_LOOP: TOKEN_DO R_LOCAL_STATEMENT TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI  */
#line 504 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_DO_WHILE);
                        
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                            NodeAddChild(yyval.treeNode, yyvsp[-5].treeNode);      // if true
                        }
#line 2080 "Parser.tab.c"
    break;

  case 47: /* R_FOR_LOOP: TOKEN_FOR TOKEN_LEFT_PARENTHESES R_FOR_INIT_FIELD TOKEN_SEMI R_EXP TOKEN_SEMI R_FOR_ASSIGNMENT_FIELD TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT  */
#line 513 "Parser/Parser.y"
                        {
                            TreeNode_st* pNode = yyvsp[0].treeNode;
                            TreeNode_st* pNodeWhile;

                            if (pNode != NULL)
                            { 
                                while (pNode->pSibling != NULL)
                                {
                                    pNode = pNode->pSibling;    
                                }                                        
                                pNode->pSibling = yyvsp[-2].treeNode;
                            }
                            else
                            {
                                yyval.treeNode = yyvsp[-2].treeNode;
                            }
                            
                            NodeCreate(&pNodeWhile, NODE_WHILE);
                        
                            NodeAddChild(pNodeWhile, yyvsp[-4].treeNode);      // Condition
                            NodeAddChild(pNodeWhile, yyvsp[0].treeNode);      // if true
                            
                            yyvsp[-6].treeNode->pSibling = pNodeWhile;
                            yyval.treeNode = yyvsp[-6].treeNode;
                        }
#line 2110 "Parser.tab.c"
    break;

  case 48: /* R_FOR_INIT_FIELD: TOKEN_ID TOKEN_ASSIGN R_EXP  */
#line 541 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild(yyval.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                        }
#line 2126 "Parser.tab.c"
    break;

  case 49: /* R_FOR_ASSIGNMENT_FIELD: R_SIMPLE_VAR_ASSIGN  */
#line 556 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2134 "Parser.tab.c"
    break;

  case 50: /* R_FOR_ASSIGNMENT_FIELD: R_COMPOUND_VAR_ASSIGN  */
#line 561 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2142 "Parser.tab.c"
    break;

  case 51: /* R_FOR_ASSIGNMENT_FIELD: R_INC_DEC  */
#line 566 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2150 "Parser.tab.c"
    break;

  case 52: /* R_LABEL: TOKEN_ID TOKEN_COLON  */
#line 577 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_LABEL);
                                yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                            }
#line 2159 "Parser.tab.c"
    break;

  case 53: /* R_FUNC_SIGNATURE: R_VAR_PREAMBLE TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES  */
#line 589 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_FUNCTION);
                                yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);
                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);

                                currentFunction = yyvsp[-3].nodeData.sVal;
                            }
#line 2173 "Parser.tab.c"
    break;

  case 54: /* R_FUNC_PROTOTYPE: R_FUNC_SIGNATURE TOKEN_SEMI  */
#line 603 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 2181 "Parser.tab.c"
    break;

  case 55: /* R_FUNC_IMPLEMENT: R_FUNC_SIGNATURE R_COMPOUND_STATEMENT  */
#line 610 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                                NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                            }
#line 2190 "Parser.tab.c"
    break;

  case 56: /* R_FUNC_CALL: TOKEN_ID TOKEN_LEFT_PARENTHESES R_EXP_LIST TOKEN_RIGHT_PARENTHESES  */
#line 618 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_FUNCTION_CALL);
                                yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2201 "Parser.tab.c"
    break;

  case 57: /* R_EXP_LIST: %empty  */
#line 628 "Parser/Parser.y"
                {
                    yyval.treeNode = NULL;
                }
#line 2209 "Parser.tab.c"
    break;

  case 58: /* R_EXP_LIST: R_EXP_LIST TOKEN_COMMA R_EXP  */
#line 633 "Parser/Parser.y"
                {
                    TreeNode_st* pNode = yyvsp[-2].treeNode;

                    if (pNode != NULL)
                    { 
                        while (pNode->pSibling != NULL)
                        {
                            pNode = pNode->pSibling;    
                        }                                        
                        pNode->pSibling = yyvsp[0].treeNode;
                        yyval.treeNode = yyvsp[-2].treeNode; 
                    }
                    else
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
                    pTreeRoot = yyval.treeNode;
                }
#line 2232 "Parser.tab.c"
    break;

  case 59: /* R_EXP_LIST: R_EXP  */
#line 653 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2240 "Parser.tab.c"
    break;

  case 60: /* R_ARG_LIST: %empty  */
#line 661 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_NULL);
                            }
#line 2248 "Parser.tab.c"
    break;

  case 61: /* R_ARG_LIST: R_ARG_LIST TOKEN_COMMA R_ARG  */
#line 666 "Parser/Parser.y"
                            {
                                TreeNode_st *pNode = yyvsp[-2].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-2].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                            }
#line 2270 "Parser.tab.c"
    break;

  case 62: /* R_ARG_LIST: R_ARG  */
#line 685 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2278 "Parser.tab.c"
    break;

  case 63: /* R_ARG: R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 692 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-2].treeNode->pSibling = yyvsp[-3].treeNode;
                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2292 "Parser.tab.c"
    break;

  case 64: /* R_ARG: R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 703 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2305 "Parser.tab.c"
    break;

  case 65: /* R_ARG: R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 713 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2318 "Parser.tab.c"
    break;

  case 66: /* R_ARG: R_TYPE_ALL TOKEN_ID  */
#line 723 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2329 "Parser.tab.c"
    break;

  case 67: /* R_VAR_DECLARATION: R_VAR_PREAMBLE R_ID_LIST TOKEN_SEMI  */
#line 738 "Parser/Parser.y"
                            {   
                                TreeNode_st* pNode =  yyvsp[-1].treeNode;

                                TreeNode_st nodePreambleCopy;
                                memcpy(&nodePreambleCopy, yyvsp[-2].treeNode, sizeof(TreeNode_st));
                                free(yyvsp[-2].treeNode);

                                do
                                {
                                    if(pNode->nodeType == NODE_VAR_DECLARATION)
                                    {
                                        NodeAddChildCopy(pNode, &nodePreambleCopy);
                                    }

                                    pNode = pNode->pSibling;    
                                }while (pNode != NULL); 

                                yyval.treeNode = yyvsp[-1].treeNode; 
                            }
#line 2353 "Parser.tab.c"
    break;

  case 68: /* R_VAR_DECLARATION: R_ARR_DECLARATION  */
#line 759 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode; 
                            }
#line 2361 "Parser.tab.c"
    break;

  case 69: /* R_ARR_DECLARATION: R_VAR_PREAMBLE TOKEN_ID R_ARR_SIZE TOKEN_SEMI  */
#line 769 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_ARRAY_DECLARATION);
                            yyval.treeNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;
                            
                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2373 "Parser.tab.c"
    break;

  case 70: /* R_ARR_SIZE: TOKEN_LEFT_BRACKET TOKEN_NUM TOKEN_RIGHT_BRACKET  */
#line 780 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                            yyval.treeNode->nodeData.dVal = yyvsp[-1].nodeData.dVal;
                        }
#line 2382 "Parser.tab.c"
    break;

  case 71: /* R_ID_LIST: R_ID_LIST TOKEN_COMMA TOKEN_ID  */
#line 789 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode; 
                          
                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                        pNode = yyvsp[-2].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            yyval.treeNode = yyvsp[-2].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = pNewNode;
                        }
                    }
#line 2410 "Parser.tab.c"
    break;

  case 72: /* R_ID_LIST: R_ID_LIST TOKEN_COMMA R_SIMPLE_VAR_ASSIGN  */
#line 814 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode;
                        pNode = yyvsp[0].treeNode->pChilds;   //Var indentifier - first child


                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = pNode->nodeData.sVal;


                        pNode = yyvsp[-2].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            yyval.treeNode = yyvsp[-2].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = pNewNode;
                        }

                        pNewNode->pSibling = yyvsp[0].treeNode;
                    }
#line 2443 "Parser.tab.c"
    break;

  case 73: /* R_ID_LIST: R_SIMPLE_VAR_ASSIGN  */
#line 844 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        pNode = yyvsp[0].treeNode->pChilds;   //Var indentifier - first child

                        NodeCreate(&(yyval.treeNode), NODE_VAR_DECLARATION);
                        yyval.treeNode->nodeData.sVal = pNode->nodeData.sVal;

                        yyval.treeNode->pSibling = yyvsp[0].treeNode;
                    }
#line 2457 "Parser.tab.c"
    break;

  case 74: /* R_ID_LIST: TOKEN_ID  */
#line 855 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_VAR_DECLARATION);
                        yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                    }
#line 2466 "Parser.tab.c"
    break;

  case 75: /* R_VAR_ASSIGNMENT: R_SIMPLE_VAR_ASSIGN TOKEN_SEMI  */
#line 866 "Parser/Parser.y"
                        {                                                               //var &= 4;
                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2474 "Parser.tab.c"
    break;

  case 76: /* R_VAR_ASSIGNMENT: R_COMPOUND_VAR_ASSIGN TOKEN_SEMI  */
#line 871 "Parser/Parser.y"
                        {
                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2482 "Parser.tab.c"
    break;

  case 77: /* R_VAR_ASSIGNMENT: R_ARRAY_INDEX TOKEN_ASSIGN R_EXP TOKEN_SEMI  */
#line 876 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2494 "Parser.tab.c"
    break;

  case 78: /* R_VAR_ASSIGNMENT: R_POINTER_CONTENT TOKEN_ASSIGN R_EXP TOKEN_SEMI  */
#line 885 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2506 "Parser.tab.c"
    break;

  case 79: /* R_COMPOUND_VAR_ASSIGN: TOKEN_ID R_COMPOUND_ASSIGN_OPERATOR R_EXP  */
#line 896 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeAddNewChild(yyvsp[-1].treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode);

                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2521 "Parser.tab.c"
    break;

  case 80: /* R_SIMPLE_VAR_ASSIGN: TOKEN_ID TOKEN_ASSIGN R_EXP  */
#line 910 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild(yyval.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                        }
#line 2537 "Parser.tab.c"
    break;

  case 81: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 927 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-3].treeNode;
                                yyvsp[-3].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2548 "Parser.tab.c"
    break;

  case 82: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL  */
#line 935 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2558 "Parser.tab.c"
    break;

  case 83: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 942 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2568 "Parser.tab.c"
    break;

  case 84: /* R_VAR_PREAMBLE: R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 949 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2578 "Parser.tab.c"
    break;

  case 85: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_TYPE_ALL  */
#line 956 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2587 "Parser.tab.c"
    break;

  case 86: /* R_VAR_PREAMBLE: R_MOD_QUALIFIER R_TYPE_ALL  */
#line 962 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2596 "Parser.tab.c"
    break;

  case 87: /* R_VAR_PREAMBLE: R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 968 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2605 "Parser.tab.c"
    break;

  case 88: /* R_VAR_PREAMBLE: R_TYPE_ALL  */
#line 974 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode; 
                            }
#line 2613 "Parser.tab.c"
    break;

  case 89: /* R_EXP: TOKEN_MINUS R_EXP  */
#line 984 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_MINUS;

                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);  
                }
#line 2624 "Parser.tab.c"
    break;

  case 90: /* R_EXP: R_EXP R_ARITHMETIC_OPERATOR R_TERM  */
#line 992 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2635 "Parser.tab.c"
    break;

  case 91: /* R_EXP: R_EXP R_CONDITION_OPERATOR R_TERM  */
#line 1000 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2646 "Parser.tab.c"
    break;

  case 92: /* R_EXP: R_EXP R_BITWISE_OPERATOR R_TERM  */
#line 1008 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode; 
                }
#line 2657 "Parser.tab.c"
    break;

  case 93: /* R_EXP: TOKEN_BITWISE_NOT R_TERM  */
#line 1016 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_BITWISE_NOT;
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode); 
                }
#line 2667 "Parser.tab.c"
    break;

  case 94: /* R_EXP: R_EXP R_LOGIC_OPERATOR R_TERM  */
#line 1023 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2678 "Parser.tab.c"
    break;

  case 95: /* R_EXP: R_EXP TOKEN_TERNARY R_EXP TOKEN_COLON R_EXP  */
#line 1031 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_TERNARY);

                    NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode); 
                    NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);   
                }
#line 2690 "Parser.tab.c"
    break;

  case 96: /* R_EXP: R_TERM  */
#line 1040 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2698 "Parser.tab.c"
    break;

  case 97: /* R_TERM: R_TERM R_PRIORITY_OPERATOR R_OPERAND  */
#line 1049 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 
                    
                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2709 "Parser.tab.c"
    break;

  case 98: /* R_TERM: R_OPERAND  */
#line 1057 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2717 "Parser.tab.c"
    break;

  case 99: /* R_OPERAND: R_INC_DEC  */
#line 1064 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2725 "Parser.tab.c"
    break;

  case 100: /* R_OPERAND: TOKEN_LOGICAL_NOT R_FACTOR  */
#line 1069 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_LOGICAL_NOT;

                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                }
#line 2736 "Parser.tab.c"
    break;

  case 101: /* R_OPERAND: R_TYPE_CAST R_FACTOR  */
#line 1077 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode);
                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2745 "Parser.tab.c"
    break;

  case 102: /* R_OPERAND: R_FACTOR  */
#line 1083 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode; 
                }
#line 2753 "Parser.tab.c"
    break;

  case 103: /* R_FACTOR: TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES  */
#line 1092 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[-1].treeNode;
                }
#line 2761 "Parser.tab.c"
    break;

  case 104: /* R_FACTOR: R_ARRAY_INDEX  */
#line 1097 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2769 "Parser.tab.c"
    break;

  case 105: /* R_FACTOR: TOKEN_MINUS TOKEN_NUM  */
#line 1102 "Parser/Parser.y"
                {   
                    NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                    yyval.treeNode->nodeData.dVal = -yyvsp[0].nodeData.dVal;
                }
#line 2778 "Parser.tab.c"
    break;

  case 106: /* R_FACTOR: TOKEN_NUM  */
#line 1108 "Parser/Parser.y"
                {   
                    NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                    yyval.treeNode->nodeData.dVal = yyvsp[0].nodeData.dVal;
                }
#line 2787 "Parser.tab.c"
    break;

  case 107: /* R_FACTOR: TOKEN_ID  */
#line 1114 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_IDENTIFIER);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2796 "Parser.tab.c"
    break;

  case 108: /* R_FACTOR: R_POINTER_CONTENT  */
#line 1120 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2804 "Parser.tab.c"
    break;

  case 109: /* R_FACTOR: TOKEN_MINUS TOKEN_FNUM  */
#line 1125 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_FLOAT);
                    yyval.treeNode->nodeData.fVal = -yyvsp[0].nodeData.fVal;
                }
#line 2813 "Parser.tab.c"
    break;

  case 110: /* R_FACTOR: TOKEN_FNUM  */
#line 1131 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_FLOAT);
                    yyval.treeNode->nodeData.fVal = yyvsp[0].nodeData.fVal;
                }
#line 2822 "Parser.tab.c"
    break;

  case 111: /* R_FACTOR: TOKEN_CNUM  */
#line 1137 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_CHAR);
                    yyval.treeNode->nodeData.dVal = yyvsp[0].nodeData.dVal;
                }
#line 2831 "Parser.tab.c"
    break;

  case 112: /* R_FACTOR: TOKEN_STR  */
#line 1143 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_STRING);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2840 "Parser.tab.c"
    break;

  case 113: /* R_FACTOR: TOKEN_BITWISE_AND R_ARRAY_INDEX  */
#line 1149 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_REFERENCE);
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);  
                }
#line 2849 "Parser.tab.c"
    break;

  case 114: /* R_FACTOR: TOKEN_BITWISE_AND TOKEN_ID  */
#line 1156 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_REFERENCE);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2858 "Parser.tab.c"
    break;

  case 115: /* R_FACTOR: R_FUNC_CALL  */
#line 1162 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2866 "Parser.tab.c"
    break;

  case 116: /* R_ARRAY_INDEX: TOKEN_ID TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET  */
#line 1169 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_ARRAY_INDEX);
                    yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);  
                }
#line 2877 "Parser.tab.c"
    break;

  case 117: /* R_POINTER_CONTENT: TOKEN_ASTERISK TOKEN_ID  */
#line 1179 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_POINTER_CONTENT);
                        yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                    }
#line 2886 "Parser.tab.c"
    break;

  case 118: /* R_INC_DEC: R_PRE_INCREMENT  */
#line 1188 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2894 "Parser.tab.c"
    break;

  case 119: /* R_INC_DEC: R_POST_INCREMENT  */
#line 1193 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2902 "Parser.tab.c"
    break;

  case 120: /* R_INC_DEC: R_PRE_DECREMENT  */
#line 1198 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2910 "Parser.tab.c"
    break;

  case 121: /* R_INC_DEC: R_POST_DECREMENT  */
#line 1203 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2918 "Parser.tab.c"
    break;

  case 122: /* R_PRE_INCREMENT: TOKEN_INCREMENT TOKEN_ID  */
#line 1211 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_PRE_INC);
                            yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                        }
#line 2927 "Parser.tab.c"
    break;

  case 123: /* R_POST_INCREMENT: TOKEN_ID TOKEN_INCREMENT  */
#line 1219 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_POST_INC);
                            yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal; 
                        }
#line 2936 "Parser.tab.c"
    break;

  case 124: /* R_PRE_DECREMENT: TOKEN_DECREMENT TOKEN_ID  */
#line 1227 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_PRE_DEC);
                            yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal; 
                        }
#line 2945 "Parser.tab.c"
    break;

  case 125: /* R_POST_DECREMENT: TOKEN_ID TOKEN_DECREMENT  */
#line 1235 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_POST_DEC);
                            yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                        }
#line 2954 "Parser.tab.c"
    break;

  case 126: /* R_ARITHMETIC_OPERATOR: TOKEN_PLUS  */
#line 1248 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_PLUS;
                            }
#line 2963 "Parser.tab.c"
    break;

  case 127: /* R_ARITHMETIC_OPERATOR: TOKEN_MINUS  */
#line 1254 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MINUS;
                            }
#line 2972 "Parser.tab.c"
    break;

  case 128: /* R_ARITHMETIC_OPERATOR: TOKEN_RIGHT_SHIFT  */
#line 1260 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_RIGHT_SHIFT;
                            }
#line 2981 "Parser.tab.c"
    break;

  case 129: /* R_ARITHMETIC_OPERATOR: TOKEN_LEFT_SHIFT  */
#line 1266 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LEFT_SHIFT;
                            }
#line 2990 "Parser.tab.c"
    break;

  case 130: /* R_PRIORITY_OPERATOR: TOKEN_ASTERISK  */
#line 1274 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MULTIPLY;
                            }
#line 2999 "Parser.tab.c"
    break;

  case 131: /* R_PRIORITY_OPERATOR: TOKEN_OVER  */
#line 1280 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_DIVIDE;
                            }
#line 3008 "Parser.tab.c"
    break;

  case 132: /* R_PRIORITY_OPERATOR: TOKEN_PERCENT  */
#line 1286 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_REMAIN;
                            }
#line 3017 "Parser.tab.c"
    break;

  case 133: /* R_CONDITION_OPERATOR: TOKEN_GREATER_THAN  */
#line 1294 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_GREATER_THAN;
                            }
#line 3026 "Parser.tab.c"
    break;

  case 134: /* R_CONDITION_OPERATOR: TOKEN_LESS_THAN_OR_EQUAL  */
#line 1300 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LESS_THAN_OR_EQUAL;
                            }
#line 3035 "Parser.tab.c"
    break;

  case 135: /* R_CONDITION_OPERATOR: TOKEN_GREATER_THAN_OR_EQUAL  */
#line 1306 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_GREATER_THAN_OR_EQUAL;
                            }
#line 3044 "Parser.tab.c"
    break;

  case 136: /* R_CONDITION_OPERATOR: TOKEN_LESS_THAN  */
#line 1312 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LESS_THAN;
                            }
#line 3053 "Parser.tab.c"
    break;

  case 137: /* R_CONDITION_OPERATOR: TOKEN_EQUAL  */
#line 1318 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_EQUAL;
                            }
#line 3062 "Parser.tab.c"
    break;

  case 138: /* R_CONDITION_OPERATOR: TOKEN_NOT_EQUAL  */
#line 1324 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_NOT_EQUAL;
                            }
#line 3071 "Parser.tab.c"
    break;

  case 139: /* R_LOGIC_OPERATOR: TOKEN_LOGICAL_AND  */
#line 1332 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LOGICAL_AND;
                            }
#line 3080 "Parser.tab.c"
    break;

  case 140: /* R_LOGIC_OPERATOR: TOKEN_LOGICAL_OR  */
#line 1338 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LOGICAL_OR;
                            }
#line 3089 "Parser.tab.c"
    break;

  case 141: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_AND  */
#line 1346 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_AND;
                            }
#line 3098 "Parser.tab.c"
    break;

  case 142: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_OR  */
#line 1352 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_OR;
                            }
#line 3107 "Parser.tab.c"
    break;

  case 143: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_XOR  */
#line 1358 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_XOR;
                            }
#line 3116 "Parser.tab.c"
    break;

  case 144: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_PLUS_ASSIGN  */
#line 1366 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_PLUS_ASSIGN;
                            }
#line 3125 "Parser.tab.c"
    break;

  case 145: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MINUS_ASSIGN  */
#line 1372 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MINUS_ASSIGN;
                            }
#line 3134 "Parser.tab.c"
    break;

  case 146: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MODULUS_ASSIGN  */
#line 1378 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MODULUS_ASSIGN;
                            }
#line 3143 "Parser.tab.c"
    break;

  case 147: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_LEFT_SHIFT_ASSIGN  */
#line 1384 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LEFT_SHIFT_ASSIGN;
                            }
#line 3152 "Parser.tab.c"
    break;

  case 148: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_RIGHT_SHIFT_ASSIGN  */
#line 1390 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_RIGHT_SHIFT_ASSIGN;
                            }
#line 3161 "Parser.tab.c"
    break;

  case 149: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_AND_ASSIGN  */
#line 1396 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_AND_ASSIGN;
                            }
#line 3170 "Parser.tab.c"
    break;

  case 150: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_OR_ASSIGN  */
#line 1402 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_OR_ASSIGN;
                            }
#line 3179 "Parser.tab.c"
    break;

  case 151: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_XOR_ASSIGN  */
#line 1408 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_XOR_ASSIGN;
                            }
#line 3188 "Parser.tab.c"
    break;

  case 152: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MULTIPLY_ASSIGN  */
#line 1414 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MULTIPLY_ASSIGN;
                            }
#line 3197 "Parser.tab.c"
    break;

  case 153: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_DIVIDE_ASSIGN  */
#line 1420 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_DIVIDE_ASSIGN;
                            }
#line 3206 "Parser.tab.c"
    break;

  case 154: /* R_TYPE_CAST: TOKEN_LEFT_PARENTHESES R_TYPE_ALL TOKEN_RIGHT_PARENTHESES  */
#line 1433 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_TYPE_CAST);
                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 3215 "Parser.tab.c"
    break;

  case 155: /* R_TYPE_ALL: R_TYPE  */
#line 1442 "Parser/Parser.y"
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;  
                                }
#line 3223 "Parser.tab.c"
    break;

  case 156: /* R_TYPE_ALL: R_TYPE_PTR  */
#line 1447 "Parser/Parser.y"
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
#line 3231 "Parser.tab.c"
    break;

  case 157: /* R_TYPE_PTR: R_TYPE TOKEN_ASTERISK  */
#line 1455 "Parser/Parser.y"
                                {  
                                    NodeCreate(&(yyval.treeNode), NODE_POINTER);

                                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);                                
                                }
#line 3241 "Parser.tab.c"
    break;

  case 158: /* R_TYPE: TOKEN_CHAR  */
#line 1466 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_CHAR;
                                }
#line 3250 "Parser.tab.c"
    break;

  case 159: /* R_TYPE: TOKEN_SHORT  */
#line 1472 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_SHORT;
                                }
#line 3259 "Parser.tab.c"
    break;

  case 160: /* R_TYPE: TOKEN_INT  */
#line 1478 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_INT;
                                }
#line 3268 "Parser.tab.c"
    break;

  case 161: /* R_TYPE: TOKEN_LONG  */
#line 1484 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_LONG;
                                }
#line 3277 "Parser.tab.c"
    break;

  case 162: /* R_TYPE: TOKEN_FLOAT  */
#line 1490 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_FLOAT;
                                }
#line 3286 "Parser.tab.c"
    break;

  case 163: /* R_TYPE: TOKEN_DOUBLE  */
#line 1496 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_DOUBLE;
                                }
#line 3295 "Parser.tab.c"
    break;

  case 164: /* R_TYPE: TOKEN_LONG TOKEN_DOUBLE  */
#line 1502 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_LONG_DOUBLE;
                                }
#line 3304 "Parser.tab.c"
    break;

  case 165: /* R_TYPE: TOKEN_VOID  */
#line 1507 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_VOID;
                                }
#line 3313 "Parser.tab.c"
    break;

  case 166: /* R_VISIBILITY_QUALIFIER: TOKEN_STATIC  */
#line 1516 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_VISIBILITY);
                                    yyval.treeNode->nodeData.dVal = (long int) VIS_STATIC;    
                                }
#line 3322 "Parser.tab.c"
    break;

  case 167: /* R_VISIBILITY_QUALIFIER: TOKEN_EXTERN  */
#line 1522 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_VISIBILITY);
                                    yyval.treeNode->nodeData.dVal = (long int) VIS_EXTERN;     
                                }
#line 3331 "Parser.tab.c"
    break;

  case 168: /* R_MOD_QUALIFIER: TOKEN_CONSTANT  */
#line 1532 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_MODIFIER);
                                    yyval.treeNode->nodeData.dVal = (long int) MOD_CONST;
                                }
#line 3340 "Parser.tab.c"
    break;

  case 169: /* R_MOD_QUALIFIER: TOKEN_VOLATILE  */
#line 1538 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_MODIFIER);
                                    yyval.treeNode->nodeData.dVal = (long int) MOD_VOLATILE; 
                                }
#line 3349 "Parser.tab.c"
    break;

  case 170: /* R_SIGN_QUALIFIER: TOKEN_SIGNED  */
#line 1546 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_SIGN);
                                    yyval.treeNode->nodeData.dVal = (long int) SIGN_SIGNED; 
                                }
#line 3358 "Parser.tab.c"
    break;

  case 171: /* R_SIGN_QUALIFIER: TOKEN_UNSIGNED  */
#line 1552 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_SIGN);
                                    yyval.treeNode->nodeData.dVal = (long int) SIGN_UNSIGNED;
                                }
#line 3367 "Parser.tab.c"
    break;


#line 3371 "Parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1557 "Parser/Parser.y"



//--------------------------------------------------------------------------------------------------------------------//
// Code
//--------------------------------------------------------------------------------------------------------------------//
int executeParser(TreeNode_st** ppTreeRoot)
{
    int ret;

    if (!ppTreeRoot)
        return -EINVAL;
    
    ret = initLexer();
    if (ret < 0)
    {
        LOG_ERROR("Failed to get source file!\n");
        return ret; 
    }

    LOG_WARNING("\n--------------Parser Start--------------\n");

    ret = yyparse();

    *ppTreeRoot = pTreeRoot;

    return ret;
}


int yyerror(char* pStr)
{
    if (!pStr)
        return -EINVAL;

    LOG_ERROR("Error at line: %lu | Error was: %s\n", getLineNumber(), pStr);

    return 0;
}


const char* getTokenName(int tokenValue) 
{
    return yysymbol_name(YYTRANSLATE(tokenValue));
}

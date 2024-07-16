%option noyywrap
%x INCOMMENT   

%{
#include <stdio.h>
#include <stdbool.h>
#include "../main.h"
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../Output/Parser.tab.h"
#include "../Lexer/Lexer.h"

#define YYSTYPE ParserObject_ut
#define YY_BUFFER_SIZE 32                      // alter to define the value of the input buffer

static char yy_buffer[YY_BUFFER_SIZE];
static char* yy_buf_pos = yy_buffer;
static size_t yy_buf_size = 0;
static int endOfFileReached = 0;

/*
   1st IF: The macro checks if the current position (yy_buf_pos) in the buffer
   has reached the end. If so, it refills the buffer by reading a block
   of characters from the input file.

   2nd IF: If the buffer is fully consumed and the file has no more characters,
   it indicates end-of-file by setting 'result' to YY_NULL, and the
   scanning loop is terminated.

   3rd IF: Characters are then copied from the buffer to the provided 'buf' until
   'max_size' is reached. The 'yy_buf_pos' is updated to point to the
   next position in the buffer.
*/
#define YY_INPUT(buf,result,max_size) \
{ \
    if (!endOfFileReached && yy_buf_pos >= yy_buffer + yy_buf_size) { \
        memset(yy_buffer, 0, YY_BUFFER_SIZE); \
        yy_buf_size = fread(yy_buffer, 1, YY_BUFFER_SIZE, yyin); \
        yy_buf_pos = yy_buffer; \
        if (yy_buf_size <= 0) { \
            endOfFileReached = 1; \
            result = YY_NULL; \
        } \
    } \
    size_t n = YY_BUFFER_SIZE - (yy_buf_pos - yy_buffer); \
    if (n > max_size) n = max_size; \
    memcpy(buf, yy_buf_pos, n); \
    yy_buf_pos += n; \
    result = n; \
}

%}

digit       [0-9]
number      {digit}+
hexNumber   0[xX][0-9a-fA-F]+
binNumber   0[bB][01]+
floatNumber {digit}*"."{digit}+({expo}{digit}+)?

identifier  [a-zA-Z_][a-zA-Z0-9_]*
string ["]([^"\\\n]|\\.|\\\n)*["]
char '([^'\\\n]|\\.)'
newline     \n
sign        ([-+])
expo        [eE]{sign}?
whitespace  [ \t]+

%%
"break"         { LOG_DEBUG_SHORT("BREAK ");                 return TOKEN_BREAK;        }
"case"          { LOG_DEBUG_SHORT("CASE ");                  return TOKEN_CASE;         }
"char"          { LOG_DEBUG_SHORT("CHAR ");                  return TOKEN_CHAR;         }
"const"         { LOG_DEBUG_SHORT("CONST ");                 return TOKEN_CONSTANT;     }
"continue"      { LOG_DEBUG_SHORT("CONTINUE ");              return TOKEN_CONTINUE;     }
"default"       { LOG_DEBUG_SHORT("DEFAULT ");               return TOKEN_DEFAULT;      }
"do"            { LOG_DEBUG_SHORT("DO ");                    return TOKEN_DO;           }
"double"        { LOG_DEBUG_SHORT("DOUBLE ");                return TOKEN_DOUBLE;       }
"if"            { LOG_DEBUG_SHORT("IF ");                    return TOKEN_IF;           }
"else"          { LOG_DEBUG_SHORT("ELSE ");                  return TOKEN_ELSE;         }
"enum"          { LOG_DEBUG_SHORT("ENUM ");                  return TOKEN_ENUM;         }
"extern"        { LOG_DEBUG_SHORT("EXTERN ");                return TOKEN_EXTERN;       }    
"float"         { LOG_DEBUG_SHORT("FLOAT ");                 return TOKEN_FLOAT;        }
"for"           { LOG_DEBUG_SHORT("FOR ");                   return TOKEN_FOR;          }
"goto"          { LOG_DEBUG_SHORT("GOTO ");                  return TOKEN_GOTO;         }
"long"          { LOG_DEBUG_SHORT("LONG ");                  return TOKEN_LONG;         }
"int"           { LOG_DEBUG_SHORT("INT ");                   return TOKEN_INT;          }
"return"        { LOG_DEBUG_SHORT("RETURN ");                return TOKEN_RETURN;       }
"short"         { LOG_DEBUG_SHORT("SHORT ");                 return TOKEN_SHORT;        }
"signed"        { LOG_DEBUG_SHORT("SIGNED ");                return TOKEN_SIGNED;       }
"sizeof"        { LOG_DEBUG_SHORT("SIZEOF ");                return TOKEN_SIZEOF;       }
"static"        { LOG_DEBUG_SHORT("STATIC ");                return TOKEN_STATIC;       }
"struct"        { LOG_DEBUG_SHORT("STRUCT ");                return TOKEN_STRUCT;       }
"switch"        { LOG_DEBUG_SHORT("SWITCH ");                return TOKEN_SWITCH;       }
"typedef"       { LOG_DEBUG_SHORT("TYPEDEF ");               return TOKEN_TYPEDEF;      }
"union"         { LOG_DEBUG_SHORT("UNION ");                 return TOKEN_UNION;        }
"unsigned"      { LOG_DEBUG_SHORT("UNSIGNED ");              return TOKEN_UNSIGNED;     }
"void"          { LOG_DEBUG_SHORT("VOID ");                  return TOKEN_VOID;         }
"volatile"      { LOG_DEBUG_SHORT("VOLATILE ");              return TOKEN_VOLATILE;     }
"while"         { LOG_DEBUG_SHORT("WHILE ");                 return TOKEN_WHILE;        }
"+"             { LOG_DEBUG_SHORT("PLUS ");                  return TOKEN_PLUS;         }
"-"             { LOG_DEBUG_SHORT("MINUS ");                 return TOKEN_MINUS;        }
"*"             { LOG_DEBUG_SHORT("ASTERISK ");              return TOKEN_ASTERISK;     }
"/"             { LOG_DEBUG_SHORT("OVER ");                  return TOKEN_OVER;         }
"%"             { LOG_DEBUG_SHORT("PERCENT ");               return TOKEN_PERCENT;      }
"++"            { LOG_DEBUG_SHORT("INCREMENT ");             return TOKEN_INCREMENT;    }
"--"            { LOG_DEBUG_SHORT("DECREMENT ");             return TOKEN_DECREMENT;    }
"&"             { LOG_DEBUG_SHORT("BITWISE_AND ");           return TOKEN_BITWISE_AND;  }
"|"             { LOG_DEBUG_SHORT("BITWISE_OR ");            return TOKEN_BITWISE_OR;   }
"~"             { LOG_DEBUG_SHORT("BITWISE_NOT ");           return TOKEN_BITWISE_NOT;  }
"^"             { LOG_DEBUG_SHORT("BITWISE_XOR ");           return TOKEN_BITWISE_XOR;  }
"!"             { LOG_DEBUG_SHORT("LOGICAL_NOT ");           return TOKEN_LOGICAL_NOT;  }
"&&"            { LOG_DEBUG_SHORT("LOGICAL_AND ");           return TOKEN_LOGICAL_AND;  }
"||"            { LOG_DEBUG_SHORT("LOGICAL_OR ");            return TOKEN_LOGICAL_OR;   }
"=="            { LOG_DEBUG_SHORT("EQUAL ");                 return TOKEN_EQUAL;        }
"!="            { LOG_DEBUG_SHORT("NOT_EQUAL ");             return TOKEN_NOT_EQUAL;    }
"<"             { LOG_DEBUG_SHORT("LESS_THAN ");             return TOKEN_LESS_THAN;    }
">"             { LOG_DEBUG_SHORT("GREATER_THAN ");          return TOKEN_GREATER_THAN; }
"<="            { LOG_DEBUG_SHORT("LESS_THAN_OR_EQUAL ");    return TOKEN_LESS_THAN_OR_EQUAL;    }
">="            { LOG_DEBUG_SHORT("GREATER_THAN_OR_EQUAL "); return TOKEN_GREATER_THAN_OR_EQUAL; }
">>"            { LOG_DEBUG_SHORT("RIGHT_SHIFT ");           return TOKEN_RIGHT_SHIFT;           }
"<<"            { LOG_DEBUG_SHORT("LEFT_SHIFT ");            return TOKEN_LEFT_SHIFT;            }
"="             { LOG_DEBUG_SHORT("ASSIGN ");                return TOKEN_ASSIGN;                }
"+="            { LOG_DEBUG_SHORT("PLUS_ASSIGN ");           return TOKEN_PLUS_ASSIGN;           }
"-="            { LOG_DEBUG_SHORT("MINUS_ASSIGN ");          return TOKEN_MINUS_ASSIGN;          }
"*="            { LOG_DEBUG_SHORT("MULTIPLY_ASSIGN ");       return TOKEN_MULTIPLY_ASSIGN;       }
"/="            { LOG_DEBUG_SHORT("DIVIDE_ASSIGN ");         return TOKEN_DIVIDE_ASSIGN;         }
"%="            { LOG_DEBUG_SHORT("MODULUS_ASSIGN ");        return TOKEN_MODULUS_ASSIGN;        }
"&="            { LOG_DEBUG_SHORT("AND_ASSIGN ");            return TOKEN_BITWISE_AND_ASSIGN;    }
">>="           { LOG_DEBUG_SHORT("RIGHT_SHIFT_ASSIGN ");    return TOKEN_RIGHT_SHIFT_ASSIGN;    }
"<<="           { LOG_DEBUG_SHORT("LEFT_SHIFT_ASSIGN ");     return TOKEN_LEFT_SHIFT_ASSIGN;     }
"|="            { LOG_DEBUG_SHORT("OR_ASSIGN ");             return TOKEN_BITWISE_OR_ASSIGN;     }
"^="            { LOG_DEBUG_SHORT("XOR_ASSIGN ");            return TOKEN_BITWISE_XOR_ASSIGN;    }
";"             { LOG_DEBUG_SHORT("SEMI ");                  return TOKEN_SEMI;                  }
","             { LOG_DEBUG_SHORT("COMMA ");                 return TOKEN_COMMA;                 }
":"             { LOG_DEBUG_SHORT("COLON ");                 return TOKEN_COLON;                 }
"."             { LOG_DEBUG_SHORT("DOT ");                   return TOKEN_DOT;                   }
"("             { LOG_DEBUG_SHORT("LEFT_PAREN ");            return TOKEN_LEFT_PARENTHESES;      }
")"             { LOG_DEBUG_SHORT("RIGHT_PAREN ");           return TOKEN_RIGHT_PARENTHESES;     }
"{"             { LOG_DEBUG_SHORT("LEFT_BRACE ");            return TOKEN_LEFT_BRACE;            }
"}"             { LOG_DEBUG_SHORT("RIGHT_BRACE ");           return TOKEN_RIGHT_BRACE;           }
"["             { LOG_DEBUG_SHORT("LEFT_BRACKET ");          return TOKEN_LEFT_BRACKET;          }
"]"             { LOG_DEBUG_SHORT("RIGHT_BRACKET ");         return TOKEN_RIGHT_BRACKET;         }
"?"             { LOG_DEBUG_SHORT("TERNARY ");               return TOKEN_TERNARY;               }
"->"            { LOG_DEBUG_SHORT("ARROW ");                 return TOKEN_ARROW;                 }
"\0"            { return TOKEN_EOF; }

{char}          { LOG_DEBUG_SHORT("CHAR ");     yylval.nodeData.dVal = (long int) yytext[1];            return TOKEN_CNUM;}
{binNumber}     { LOG_DEBUG_SHORT("BIN_NUM ");  yylval.nodeData.dVal = strtol(yytext, NULL, 2);         return TOKEN_NUM; }
{hexNumber}     { LOG_DEBUG_SHORT("HEX_NUM ");  yylval.nodeData.dVal = strtol(yytext, NULL, 16);        return TOKEN_NUM; }
{number}        { LOG_DEBUG_SHORT("NUM ");      yylval.nodeData.dVal = strtol(yytext, NULL, 10);        return TOKEN_NUM; }
{string}        { LOG_DEBUG_SHORT("STR ");      StringCreateAndCopy(&(yylval.nodeData.sVal),yytext,0);  return TOKEN_STR; }
{identifier}    { LOG_DEBUG_SHORT("ID ");       StringCreateAndCopy(&(yylval.nodeData.sVal),yytext,0);  return TOKEN_ID;  }
{floatNumber}   { LOG_DEBUG_SHORT("FNUM ");     yylval.nodeData.fVal = strtod(yytext, NULL);            return TOKEN_FNUM;}
{newline}       { LOG_DEBUG_SHORT(" \n");       incrementLineNumber(1);}
{whitespace}    { /*  ignore */}

"//".*          { /* When "//" is found, zero or more occurrences of any character are ignored */}

<INITIAL>{      // INITIAL Lexical state
  "/*"          { LOG_DEBUG_SHORT(" [In comment]");}    BEGIN(INCOMMENT);
}

<INCOMMENT>{    // INCOMMENT Lexical state
  <<EOF>>       { LOG_DEBUG_SHORT(" Error: Unterminated comment\n");
                  return TOKEN_ERROR;
                }
  "*/"          { LOG_DEBUG_SHORT(" [Out comment]");}   BEGIN(INITIAL);
  "\n"          { incrementLineNumber(1);};
  [^*\n]+       ; // Consume characters within the comment block
}

<<EOF>>         {yyterminate(); return TOKEN_EOF; }

. {LOG_ERROR("[%s] is an invalid token\n", yytext); YY_FATAL_ERROR("Unrecoverable error in lexer"); return TOKEN_ERROR;}

%%

int initLexer()
{
    return getSourceFile(&yyin);
}

/// \brief
/// \return
TokenType_et getToken()
{
    int ret;
    TokenType_et currentToken;
    static bool firstTime = true;

    if (firstTime)
    {
        firstTime = false;

        ret = initLexer();
        if (ret < 0)
            return ret;
    } 

    currentToken = (TokenType_et) yylex();

    return currentToken;
}

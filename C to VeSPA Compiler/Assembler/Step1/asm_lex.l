%option noyywrap
%x INCOMMENT   

%{
#include <stdio.h> 
#include <stdbool.h> 
#include "../Util/asm_globals.h"
#include "../Util/logger.h"
#include "../Util/asm_operations.h"
#include "../Util/symbol_table.h"
#include "../Util/statements_list.h"
#include "../Step1/asm_scanner.h"
#include "../main.h"
#include "../Output/asm_parser.tab.h"


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

digit           [0-9]
hex             [a-fA-F]

dec_number      {digit}+
bin_number      [01]+b
hex_number_x    0x({digit}|{hex})+
hex_number_h    ({digit}|{hex})+[hH]

register        R({digit}|[12]{digit}|3[01])
identifier      [a-zA-Z_][a-zA-Z0-9_]*

newline         \n
carriage        \r
whitespace      [ \t]+


%%
"BRA"   { LOG_DEBUG_SHORT(" BRANCH_ALWAYS");             yylval=BRA_COND;    return TOKEN_BRANCH;  }
"BCC"   { LOG_DEBUG_SHORT(" BRANCH_CARRY_CLEAR");        yylval=BCC_COND;    return TOKEN_BRANCH;  }
"BVC"   { LOG_DEBUG_SHORT(" BRANCH_OVERFLOW_CLEAR");     yylval=BVC_COND;    return TOKEN_BRANCH;  }
"BEQ"   { LOG_DEBUG_SHORT(" BRANCH_EQUAL");              yylval=BEQ_COND;    return TOKEN_BRANCH;  }
"BGE"   { LOG_DEBUG_SHORT(" BRANCH_GREATER_EQUAL");      yylval=BGE_COND;    return TOKEN_BRANCH;  }
"BGT"   { LOG_DEBUG_SHORT(" BRANCH_GREATER");            yylval=BGT_COND;    return TOKEN_BRANCH;  }
"BPL"   { LOG_DEBUG_SHORT(" BRANCH_PLUS");               yylval=BPL_COND;    return TOKEN_BRANCH;  }
"BNV"   { LOG_DEBUG_SHORT(" BRANCH_NEVER");              yylval=BNV_COND;    return TOKEN_BRANCH;  }
"BCS"   { LOG_DEBUG_SHORT(" BRANCH_CARRY_SET");          yylval=BCS_COND;    return TOKEN_BRANCH;  }
"BVS"   { LOG_DEBUG_SHORT(" BRANCH_OVERFLOW_SET");       yylval=BVS_COND;    return TOKEN_BRANCH;  }
"BNE"   { LOG_DEBUG_SHORT(" BRANCH_NOT_EQUAL");          yylval=BNE_COND;    return TOKEN_BRANCH;  }
"BLT"   { LOG_DEBUG_SHORT(" BRANCH_LESS");               yylval=BLT_COND;    return TOKEN_BRANCH;  }
"BLE"   { LOG_DEBUG_SHORT(" BRANCH_LESS_EQUAL");         yylval=BLE_COND;    return TOKEN_BRANCH;  }
"BMI"   { LOG_DEBUG_SHORT(" BRANCH_MINUS");              yylval=BMI_COND;    return TOKEN_BRANCH;  }

"ADD"   { LOG_DEBUG_SHORT(" ADD");                       return TOKEN_ADD;             }
"SUB"   { LOG_DEBUG_SHORT(" SUB");                       return TOKEN_SUB;             }
"OR"    { LOG_DEBUG_SHORT(" OR");                        return TOKEN_OR;              }
"AND"   { LOG_DEBUG_SHORT(" AND");                       return TOKEN_AND;             }
"NOT"   { LOG_DEBUG_SHORT(" NOT");                       return TOKEN_NOT;             }
"XOR"   { LOG_DEBUG_SHORT(" XOR");                       return TOKEN_XOR;             }
"CMP"   { LOG_DEBUG_SHORT(" CMP");                       return TOKEN_CMP;             }
"RR"    { LOG_DEBUG_SHORT(" RR");                        return TOKEN_RR;              }
"RL"    { LOG_DEBUG_SHORT(" RL");                        return TOKEN_RL;              }

"MOV"   { LOG_DEBUG_SHORT(" MOVE");                      return TOKEN_MOVE;            }
"JMP"   { LOG_DEBUG_SHORT(" JUMP");                      return TOKEN_JUMP;            }
"JMPL"  { LOG_DEBUG_SHORT(" JUMP_LINK");                 return TOKEN_JUMP_LINK;       }
"LD"    { LOG_DEBUG_SHORT(" LOAD_DIRECT");               return TOKEN_LOAD_DIRECT;     }
"LDI"   { LOG_DEBUG_SHORT(" LOAD_IMMEDIATE");            return TOKEN_LOAD_IMMEDIATE;  }
"LDX"   { LOG_DEBUG_SHORT(" LOAD_INDEXED ");             return TOKEN_LOAD_INDEXED;    }
"ST"    { LOG_DEBUG_SHORT(" STORE_DIRECT");              return TOKEN_STORE_DIRECT;    }
"STX"   { LOG_DEBUG_SHORT(" STORE_INDEXED");             return TOKEN_STORE_INDEXED;   }

"RETI"  { LOG_DEBUG_SHORT(" RETI");                      return TOKEN_RETI;            }
"HALT"  { LOG_DEBUG_SHORT(" HALT");                      return TOKEN_HALT;            }
"NOP"   { LOG_DEBUG_SHORT(" NOP");                       return TOKEN_NOP;             }

".byte"  { LOG_DEBUG_SHORT(" [.BYTE]");                  return TOKEN_BYTE;            }
".word"  { LOG_DEBUG_SHORT(" [.WORD]");                  return TOKEN_WORD;            }
".alloc" { LOG_DEBUG_SHORT(" [.ALLOC]");                 return TOKEN_ALLOC;           }
".org"   { LOG_DEBUG_SHORT(" [.ORG]");                   return TOKEN_ORG;             }
".equ"   { LOG_DEBUG_SHORT(" [.EQU]");                   return TOKEN_EQU;             }

","      { LOG_DEBUG_SHORT(" COMMA");                    return TOKEN_COMMA;           }
"#"      { LOG_DEBUG_SHORT(" CARDINAL");                 return TOKEN_CARDINAL;        }
":"      { LOG_DEBUG_SHORT(" COLON");                    return TOKEN_COLON;           }
"+"      { LOG_DEBUG_SHORT(" PLUS");                     return TOKEN_PLUS;            }
"("      { LOG_DEBUG_SHORT(" LEFT_PAREN ");              return TOKEN_LEFT_PAREN;      }
")"      { LOG_DEBUG_SHORT(" RIGHT_PAREN ");             return TOKEN_RIGHT_PAREN;     }
"-"      { LOG_DEBUG_SHORT(" MINUS");                    return TOKEN_MINUS;           } 
"\0"     {                                               return TOKEN_ENDFILE;         } 

"$"      {LOG_DEBUG_SHORT(" [DOLLAR]");                  yylval = get_location_counter();    return TOKEN_DOLLAR;    }

{dec_number}    { LOG_DEBUG_SHORT(" [NUMBER]");          yylval = strtol(yytext, NULL, 10);  return TOKEN_NUMBER;    }
{hex_number_x}  { LOG_DEBUG_SHORT(" [HEX_NUMBER]");      yylval = strtol(yytext, NULL, 16);  return TOKEN_NUMBER;    }
{hex_number_h}  { LOG_DEBUG_SHORT(" [HEX_NUMBER]");      yylval = strtol(yytext, NULL, 16);  return TOKEN_NUMBER;    }
{bin_number}    { LOG_DEBUG_SHORT(" [BIN_NUMBER]");      yylval = strtol(yytext, NULL, 2);   return TOKEN_NUMBER;    }
{register}      { LOG_DEBUG_SHORT(" [REGISTER]");        sscanf(yytext, "R%d", &yylval);     return TOKEN_REG;       }
{identifier}    { LOG_DEBUG_SHORT(" [IDENTIFIER]");      yylval = add_symbol(yytext);        return TOKEN_IDENTIFIER;}

{newline}       { LOG_DEBUG_SHORT(" \n");   increment_line_number(1);}
{whitespace}    { /*  ignore */}  
{carriage}      { /*  ignore */}

"//".*          { LOG_DEBUG_SHORT(" Comment "); /* When "//" is found, zero or more occurrences of any character are ignored */}
";".*           { LOG_DEBUG_SHORT(" Comment "); /* When ";" is found, zero or more occurrences of any character are ignored */}

<INITIAL>{      // INITIAL Lexical state
  "/*"          { LOG_DEBUG_SHORT(" [In comment]");} BEGIN(INCOMMENT);      
}

<INCOMMENT>{    // INCOMMENT Lexical state
  <<EOF>>       { LOG_ERROR("[ASSEMBLER] Error: Unterminated comment\n");
                  return TOKEN_ERROR; 
                }
  "*/"          { LOG_DEBUG_SHORT(" [Out comment]");} BEGIN(INITIAL);
  "\n"          { increment_line_number(1);}
  [^*\n]+         ; // Consume characters within the comment block
}

<<EOF>>         {yyterminate();   return TOKEN_ENDFILE;}

. {LOG_ERROR("[ASSEMBLER] Error, [%s] is an invalid token\n",yytext); YY_FATAL_ERROR("Unrecoverable error in lexer"); return TOKEN_ERROR;}
%%


void init_lexer()
{
    get_source_file(&yyin);
}


TokenType getToken(void)
{ 
  static bool firstTime = true;
  TokenType currentToken;

  if (firstTime){ 
    firstTime = false;
    init_lexer();
  }

  currentToken = yylex();
  return currentToken;
}

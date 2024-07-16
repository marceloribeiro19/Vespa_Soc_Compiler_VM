%{
#include "../Util/asm_globals.h"
#include "../Step1/asm_scanner.h"
#include "../Output/asm_parser.tab.h"
#include "../Util/statements_list.h"
#include "../Util/symbol_table.h"
#include "../Util/asm_operations.h"
#include "../Util/logger.h"
#include "../main.h"

int yylex();
int yyerror(char *str);


#define NULL_ARG    0
%}

/* ---- TOKENS TYPES ----- */
%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_OR
%token TOKEN_AND
%token TOKEN_NOT
%token TOKEN_XOR
%token TOKEN_CMP
%token TOKEN_RR
%token TOKEN_RL
%token TOKEN_BRANCH
%token TOKEN_JUMP
%token TOKEN_JUMP_LINK
%token TOKEN_MOVE
%token TOKEN_LOAD_DIRECT
%token TOKEN_LOAD_IMMEDIATE
%token TOKEN_LOAD_INDEXED
%token TOKEN_STORE_DIRECT
%token TOKEN_STORE_INDEXED
%token TOKEN_RETI
%token TOKEN_HALT
%token TOKEN_NOP
%token TOKEN_NUMBER
%token TOKEN_REG
%token TOKEN_IDENTIFIER
%token TOKEN_ENDFILE
%token TOKEN_ERROR
%token TOKEN_COMMA
%token TOKEN_CARDINAL
%token TOKEN_COLON
%token TOKEN_DOLLAR  
%token TOKEN_BYTE
%token TOKEN_WORD
%token TOKEN_ALLOC
%token TOKEN_ORG
%token TOKEN_EQU
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_LEFT_PAREN
%token TOKEN_RIGHT_PAREN


%left TOKEN_PLUS TOKEN_MINUS        //left-associativity
%%

/* Program */
prog    :   prog TOKEN_ENDFILE
        |   prog stmt
        |   stmt
        ;

/* Statement */
stmt    :   add_stmt
        |   sub_stmt
        |   or_stmt
        |   and_stmt
        |   not_stmt
        |   xor_stmt
        |   cmp_stmt
        |   rr_stmt
        |   rl_stmt
        |   branch_stmt
        |   move_stmt
        |   jump_stmt
        |   load_stmt
        |   store_stmt
        |   reti_stmt
        |   halt_stmt
        |   nop_stmt
        |   byte_stmt
        |   word_stmt
        |   alloc_stmt
        |   org_stmt
        |   equ_stmt
        |   label
        ;


/* ADD Operation */
add_stmt    :   TOKEN_ADD TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                
                    {  
                        add_statement(ADD_OPCODE, $2, $4, $6, NO_TYPE); 
                    } 
            |   TOKEN_ADD TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression    
                    {
                        add_statement(ADD_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }       
            ;        

/* SUB Operation */
sub_stmt    :   TOKEN_SUB TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                
                    { 
                        add_statement(SUB_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   TOKEN_SUB TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression    
                    { 
                        add_statement(SUB_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;        

/* OR Operation */
or_stmt     :   TOKEN_OR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                  
                    { 
                        add_statement(OR_OPCODE, $2, $4, $6, NO_TYPE);    
                    }
            |   TOKEN_OR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression      
                    { 
                        add_statement(OR_OPCODE, $2, $4, $7, IMMEDIATE);   
                    } 
            ;

/* AND Operation */
and_stmt    :   TOKEN_AND TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                
                    { 
                        add_statement(AND_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   TOKEN_AND TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression   
                    { 
                        add_statement(AND_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;

/* XOR Operation */
xor_stmt    :   TOKEN_XOR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                          
                    { 
                        add_statement(XOR_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   TOKEN_XOR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression              
                    { 
                        add_statement(XOR_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;

/* NOT Operation */
not_stmt    :   TOKEN_NOT TOKEN_REG TOKEN_COMMA TOKEN_REG                          
                    { 
                        add_statement(NOT_OPCODE, $2, $4, NULL_ARG, NO_TYPE);   
                    }
            |   TOKEN_NOT TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression              
                    { 
                        add_statement(NOT_OPCODE, $2, $5, NULL_ARG, IMMEDIATE); 
                    }
            ;        

/* CMP Operation */
cmp_stmt    :   TOKEN_CMP TOKEN_REG TOKEN_COMMA TOKEN_REG                          
                    { 
                        add_statement(CMP_OPCODE, $2, $4, NULL_ARG, NO_TYPE);
                    };
            |   TOKEN_CMP TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression                        
                    { 
                        add_statement(CMP_OPCODE, $2, $5, NULL_ARG, IMMEDIATE);
                    }
            ;

/* ROTATE RIGHT Operation */
rr_stmt     :   TOKEN_RR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                
                    { 
                        add_statement(RR_OPCODE, $2, $4, $6, NO_TYPE);  
                    }

            |   TOKEN_RR TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression
                    {
                        add_statement(RR_OPCODE, $2, $5, $7, IMMEDIATE);
                    }
            ;

/* ROTATE LEFT Operation */
rl_stmt     :   TOKEN_RL TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_REG                
                    { 
                        add_statement(RL_OPCODE, $2, $4, $6, NO_TYPE);  
                    }

            |   TOKEN_RL TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression
                    {
                        add_statement(RL_OPCODE, $2, $5, $7, IMMEDIATE);
                    }
            ;

/* BRANCH Operation */
branch_stmt :   TOKEN_BRANCH TOKEN_IDENTIFIER             
                    {
                        add_statement(BXX_OPCODE, $2, $1, NULL_ARG, NO_TYPE);
                    }
            |   TOKEN_BRANCH TOKEN_CARDINAL expression
                    {
                        add_statement(BXX_OPCODE, $3, $1, NULL_ARG, IMMEDIATE); 
                    }        
            |   TOKEN_BRANCH TOKEN_DOLLAR
                    {
                        add_statement(BXX_OPCODE, $2, $1, NULL_ARG, IMMEDIATE);
                    }
            ;    

/* MOV Operation - Pseudo-instruction */
move_stmt   :   TOKEN_MOVE TOKEN_REG TOKEN_COMMA TOKEN_REG                        
                    {
                        add_statement(ADD_OPCODE, $2, $4, 0, IMMEDIATE);
                    }
            ;     


/* JUMP and JUMP with link Operations */
jump_stmt   :   TOKEN_JUMP TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression                  
                    { 
                        add_statement(JMP_OPCODE, NULL_ARG, $2, $5, IMMEDIATE); 
                    }
            |   TOKEN_JUMP_LINK TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression    
                    {
                        add_statement(JMP_OPCODE, $2, $4 , $7, LINK);
                    }
            ;        

/* Direct, Immediate and Indexed Load operations */
load_stmt   :   TOKEN_LOAD_DIRECT TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression               
                    { 
                        add_statement(LD_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   TOKEN_LOAD_IMMEDIATE TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression           
                    {
                        add_statement(LDI_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   TOKEN_LOAD_IMMEDIATE TOKEN_REG TOKEN_COMMA TOKEN_COLON TOKEN_IDENTIFIER
                    {
                        add_statement(LDI_OPCODE, $2, $5, NULL_ARG, LABEL);
                    }
            |   TOKEN_LOAD_INDEXED TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression  
                    { 
                        add_statement(LDX_OPCODE, $2, $4, $7, NO_TYPE); 
                    }
            ;

/* Direct and Indexed Store operations */
store_stmt  :   TOKEN_STORE_DIRECT TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression             
                    { 
                        add_statement(ST_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   TOKEN_STORE_INDEXED TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA TOKEN_CARDINAL expression
                    { 
                        add_statement(STX_OPCODE, $2, $4, $7, NO_TYPE);
                    }
            ;        

/* Reti operation */
reti_stmt   :   TOKEN_RETI     
                    {
                        add_statement(RETI_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Halt operation */
halt_stmt   :   TOKEN_HALT 
                    { 
                        add_statement(HLT_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Nop operation */
nop_stmt    :   TOKEN_NOP 
                    { 
                        add_statement(NOP_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Byte directive */
byte_stmt   :   TOKEN_BYTE TOKEN_NUMBER 
                    { 
                        add_statement(DOT_BYTE_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Word directive */
word_stmt   :   TOKEN_WORD TOKEN_NUMBER 
                    { 
                        add_statement(DOT_WORD_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Alloc directive */
alloc_stmt  :   TOKEN_ALLOC TOKEN_IDENTIFIER TOKEN_NUMBER
                    {
                        add_statement(DOT_ALLOC_OP, $3, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Org directive */
org_stmt    :   TOKEN_ORG TOKEN_NUMBER 
                    {
                        add_statement(DOT_ORG_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

/* Equ directive */
equ_stmt    :   TOKEN_EQU TOKEN_IDENTIFIER TOKEN_COMMA expression 
                    {
                        if(get_symbol_value($2) != UNINITIALIZED_VALUE){
                            LOG_ERROR("[ASSEMBLER] ERROR: Constant redefinition: %s in line %ld\n", get_symbol_name($1), get_line_number());
                        }
                        else{
                            set_symbol_value($2, $4);
                            $$ = $2;
                        }
                    };

/* Labels */
label       :   TOKEN_IDENTIFIER TOKEN_COLON 
                    { 
                        if(get_symbol_value($1) != UNINITIALIZED_VALUE){
                            LOG_ERROR("[ASSEMBLER] ERROR: Label redefinition: %s in line %ld\n", get_symbol_name($1), get_line_number());
                        }
                        else{
                            set_symbol_value($1, get_location_counter());
                            $$ = $1;
                        }
                    };

/* Expression: calculations made at assembly time */
expression  :   TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN
                    {
                        $$ = $2;
                    }
            |   expression TOKEN_PLUS expression
                    {
                        $$ = $$ + $3;
                    }
            |   expression TOKEN_MINUS expression
                    {
                        $$ = $$ - $3;
                    }      
            |   TOKEN_PLUS TOKEN_NUMBER
                    {
                        $$ = $2;
                    }
            |   TOKEN_MINUS TOKEN_NUMBER
                    {
                        $$ = 0 - $2;
                    }        
            |   TOKEN_NUMBER
                    {
                        $$ = $1;
                    } 
            |   TOKEN_IDENTIFIER
                    {
                        /* 
                            Checks if the constant has already been defined using the Equ directive.
                            The constant must be declared before use (SEMANTIC PART) 
                        */
                        int temp = get_symbol_value($1);

                        LOG_MESSAGE("Symbol Value: %d\n",get_symbol_value($1));

                        if(temp == UNINITIALIZED_VALUE){
                            LOG_ERROR("[ASSEMBLER] ERROR: Constant not defined: %s in line %ld\n", get_symbol_name($1), get_line_number());
                        }

                        $$ = temp;
                    }             
            ;
%%


int yyerror(char *str)
{
  	LOG_ERROR ("[ASSEMBLER] ERROR: %s in line number : %ld\n", str, get_line_number());
	return 0;
}


///hjh
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  
#include <math.h>    
#include <unistd.h>
#include "../Step2/code_generator.h"
#include "../Util/asm_operations.h"
#include "../Util/symbol_table.h"
#include "../Util/statements_list.h"
#include "../Util/logger.h"
#include "../main.h"


#define IMMED16 16
#define IMMED17 17
#define IMMED22 22
#define IMMED23 23

static FILE* fp_hex;

/* Private module functions */
static void print_code_hex(uint32_t code, uint8_t inst_size, uint32_t *lc);
static int check_immed(int32_t value, uint32_t width, uint32_t line);


/// @brief Generates the binary code using statements list, symbol table and opcode table
/// @return none
void generate_code()
{    
    uint32_t code = 0;
    statement_t current_statement;
    uint32_t lc = 0;
    uint8_t inst_size = 0;
    uint8_t error = 0;
    int32_t bxx_value = 0;
    int32_t label_value = 0;

    get_output_file(&fp_hex);

    for (uint32_t i = 0; i < get_current_stmt_index(); i++)
    {
        inst_size = 4;
        code = 0;
        current_statement = get_statement(i);
        
        switch (current_statement.op_code){
            case NOP_OPCODE:
            case HLT_OPCODE:
            case RETI_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                break;


            case NOT_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & current_statement.op1)      << 22;
                code |= (0x1f & current_statement.op2)      << 17;
                break;
                

            case ADD_OPCODE:
            case SUB_OPCODE:
            case OR_OPCODE:
            case AND_OPCODE:
            case XOR_OPCODE:
            case RR_OPCODE:
            case RL_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & current_statement.op1)      << 22;
                code |= (0x1f & current_statement.op2)      << 17;
                
                if(current_statement.misc == IMMEDIATE)
                {
                    error |= check_immed(current_statement.op3, IMMED16, i);
                    code |= 1 << 16;
                    code |= (0xffff & current_statement.op3);
                }
                else
                {
                    code |= (0x1f & current_statement.op3)  << 11;
                }
                break;


            case CMP_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & current_statement.op1)      << 17;
                        
                if(current_statement.misc == IMMEDIATE)
                {
                    error |= check_immed(current_statement.op2, IMMED16, i);
                    code |= 1 << 16;
                    code |= (0xffff & current_statement.op2);
                }
                else
                {
                    code |= (0x1f & current_statement.op2)  << 11;
                }
                break;

            case BXX_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0xf & current_statement.op2)       << 23;  
                
                if(current_statement.misc == NO_TYPE)
                {
                    if(get_symbol_value(current_statement.op1) == UNINITIALIZED_VALUE)
                    {
                        LOG_ERROR("Uninitialized symbol %d\n", get_symbol_value(current_statement.op1));
                        error = 1;
                        bxx_value = 0;
                    }
                    else
                    {
                        bxx_value = get_symbol_value(current_statement.op1) - lc - 4;
                    }
                }
                else
                {
                    bxx_value = (current_statement.op1 - lc - 4);
                }
                
                error |= check_immed(bxx_value, IMMED23, i);
                code  |= (0x7fffff & bxx_value);
                break;


            case JMP_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                
                if(current_statement.misc == LINK)
                {
                    code |= 1 << 16;
                    code |= (0x1f & current_statement.op1)  << 22;
                }
    
                code  |= (0x1f & current_statement.op2)     << 17;
                error |= check_immed((current_statement.op3), IMMED16, i);
                code  |= (0xffff & current_statement.op3);
                break;

            case ST_OPCODE:
            case LD_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & current_statement.op1)      << 22;
                
                error |= check_immed((current_statement.op2), IMMED22, i);
                code  |= (0x3fffff & (current_statement.op2));
                break;
            case LDI_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & current_statement.op1)      << 22;
                if(current_statement.misc == LABEL)
                {
                    if(get_symbol_value(current_statement.op2) == UNINITIALIZED_VALUE)
                    {
                        LOG_ERROR("Uninitialized symbol %d\n", get_symbol_value(current_statement.op2));
                        error = 1;
                        label_value = 0;
                    }
                    else
                    {
                        label_value = get_symbol_value(current_statement.op2);
                    }
                    error |= check_immed((label_value), IMMED22, i);
                    code  |= (0x3fffff & (label_value));
                }
                else
                {
                    error |= check_immed((current_statement.op2), IMMED22, i);
                    code  |= (0x3fffff & (current_statement.op2));
                }
                
                break;


            case LDX_OPCODE:
            case STX_OPCODE:
                code |= (0x1f & current_statement.op_code)  << 27;
                code |= (0x1f & (current_statement.op1))    << 22;
                code |= (0x1f & (current_statement.op2))    << 17;

                error |= check_immed((current_statement.op3), IMMED17, i);
                code  |= (0x1ffff & (current_statement.op3));
                break;

            case DOT_BYTE_OP:
                error |= check_immed(current_statement.op1, 8, i);
                code = (current_statement.op1 & 0xff);
                inst_size = 1;
                break;


            case DOT_WORD_OP:
                code = (current_statement.op1 & 0xffffffff);
                break;


            case DOT_ALLOC_OP:
                for (int j = 1; j <= current_statement.op1; j++)
                {
                    print_code_hex(0, 4, &lc);
                }
                break;


            case DOT_ORG_OP:
                lc = current_statement.op1;
                break;    


            default:
                LOG_ERROR("Invalid operation in statements list in %d line\n");
                break;
        }
        
        if (current_statement.op_code != DOT_ALLOC_OP && current_statement.op_code != DOT_ORG_OP)
        {
            print_code_hex(code, inst_size, &lc);
        }
    }

    if(error)
    {
        int fd = fileno(fp_hex);
        ftruncate(fd, 0);    //clear output file
    }
}


/// @brief Prints the generated code to a file, in hexa format
/// @param code 
/// @param inst_size 
/// @param lc 
static void print_code_hex(uint32_t code, uint8_t inst_size, uint32_t *lc)
{
    fprintf(fp_hex, "@%04x", *lc);

    for(uint8_t j = inst_size; j > 0; j--){
        fprintf(fp_hex, " %02x", (0xff & (code >> (8 * (j-1)))));
    }
    fprintf(fp_hex,"\n");

    *lc += inst_size;
}


/// @brief Checks whether the immediate value is within the range defined by the number of bits
/// @param value 
/// @param width 
/// @param line
/// @return 1 if error and 0 if no error
static int check_immed(int32_t value, uint32_t width, uint32_t line)
{
    int32_t max_possible = (1 << (width - 1)) - 1;  
    int32_t min_possible = -(1 << (width - 1));      

    if (value >= max_possible || value <= min_possible)
    {
        LOG_ERROR("ERROR in line %d: The value %d, must be within the range of [%d, %d]\n", line, value, min_possible, max_possible);
        return 1;
    }
    return 0;
}
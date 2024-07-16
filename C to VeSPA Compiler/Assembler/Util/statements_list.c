#include <stdio.h>
#include <stdlib.h>
#include "../Util/logger.h"
#include "../Util/statements_list.h"
#include "../Util/symbol_table.h"
#include "../Util/asm_operations.h"

#define INITIAL_STMT_LIST_SIZE       128
#define INC_STMT_LIST                64 
#define WORD_SIZE                    4  


static uint8_t ready = 0;
static uint32_t location_counter = 0;
static uint32_t curr_stmt = 0;
static size_t stmt_list_size = INITIAL_STMT_LIST_SIZE;
static statement_t* stmt_list;



/// @brief inits the statement list
void init_statements_list()
{
    curr_stmt = 0;
    location_counter = 0;
    
    stmt_list = (statement_t*)malloc(sizeof(statement_t) * INITIAL_STMT_LIST_SIZE);
    if(stmt_list == NULL){
        LOG_DEBUG("Error allocating memory\n");

        exit(EXIT_FAILURE);
    }

    stmt_list_size = INITIAL_STMT_LIST_SIZE;
    ready = 1;
}


/// @brief deletes the statement list
void delete_statements_list()
{
    free(stmt_list);
}


/// @brief adds a statement to the statements list
/// @param list -> pointer to statement list
/// @param op_code 
/// @param op1 
/// @param op2 
/// @param op3 
/// @param misc
uint8_t add_statement(uint32_t op_code, uint32_t op1, uint32_t op2, uint32_t op3, uint32_t misc)
{
    if(curr_stmt >= stmt_list_size){
        stmt_list_size += INC_STMT_LIST;
        stmt_list = (statement_t*) realloc(stmt_list, sizeof(statement_t) * stmt_list_size);

        if(stmt_list == NULL){
            LOG_DEBUG("Error reallocating memory\n");

            exit(EXIT_FAILURE);
        }
    }

    stmt_list[curr_stmt].op_code    = op_code;
    stmt_list[curr_stmt].op1        = op1;
    stmt_list[curr_stmt].op2        = op2;
    stmt_list[curr_stmt].op3        = op3;
    stmt_list[curr_stmt].misc       = misc;
    stmt_list[curr_stmt].line_num   = curr_stmt + 1;

    curr_stmt++;

    if(op_code == DOT_ORG_OP){
        location_counter = op1;
    }
    else{
        location_counter += WORD_SIZE;
    }
}



/// @brief returns the location counter
const uint32_t get_location_counter()
{
    return location_counter;
}

 
const statement_t get_statement(uint8_t index)
{
    return stmt_list[index];
}



const uint32_t get_current_stmt_index()
{
    return curr_stmt;
}


/// @brief prints all statements list
/// @param list 
void print_statements()
{
    printf("\n\n*************INTERMEDIATE REPRESENTATION*************\n");
    printf("LINE    OPCODE      OP1     OP2     OP3     MISC\n");
    printf("----------------------------------------------------------\n");
   
    for (int i = 0; i < curr_stmt; i++){
        printf("%02d       %02d        %03d     %03d     %03d      %d\n", stmt_list[i].line_num,
                                                                          stmt_list[i].op_code,
                                                                          stmt_list[i].op1,
                                                                          stmt_list[i].op2, 
                                                                          stmt_list[i].op3,
                                                                          stmt_list[i].misc);
    }

    printf("******************************************************\n\n");
    printf("Location counter: %d", location_counter);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "Step1/asm_scanner.h"
#include "Step2/code_generator.h"
#include "Output/asm_parser.tab.h"
#include "Util/statements_list.h"
#include "Util/symbol_table.h"
#include "Util/logger.h"


static FILE* pSourceFile;
static FILE* pOutputFile;
static size_t lineNumber = 1;


/// @brief gets the line number
/// @return line number
size_t get_line_number()
{
    return lineNumber;
}


/// @brief increments the number of lines by n units
/// @param n 
/// @return line number
size_t increment_line_number(size_t n)
{
    lineNumber += n;
    return lineNumber;
}


/// @brief gets the source file descriptor
/// @param ppFile 
void get_source_file(FILE** ppFile)
{
    *ppFile = pSourceFile;
}


/// @brief gets the ouptput file descriptor
/// @param ppFile 
void get_output_file(FILE** ppFile)
{
    *ppFile = pOutputFile;
}


/// @brief prints the eeror message when user uses an invalid command
static void print_error_message(){
    printf("Usage: <Prog> <source_file> -<prefix>\n");
    printf("PREFIX: -s : print symbol table\n");
    printf("        -i : print intermediate representation\n");
    printf("        -p : executes only step 1 (scanner and parser)\n");
    printf("        -o <filename> : specifies the output file\n\n");
}


int main(int argc, char *argv[]){
    char* str;
    uint8_t flag_symbol_table = 0;
    uint8_t flag_intermediate = 0;
    uint8_t flag_step1_only   = 0;

    init_statements_list();     //init the statements list
    init_symbol_table();        //init the symbol table
    
    if (argc < 2)
    {
        print_error_message();
        exit(-1);
    }
    else{
        pSourceFile = fopen(argv[1], "r");
        if (!pSourceFile)
        {
            printf("Failed to open source file!\n");
            exit(-1);
        }

        for (uint8_t i = 2; i < argc; i++){
            if(*argv[i] == '-'){
                str = argv[i] + 1;

                switch (*str){
                    case 'o':
                       pOutputFile = fopen(argv[i+1], "w");
                        if (!pOutputFile){
                            printf("Failed to open output file!\n");
                            exit(-1);
                        }
                       i++;
                       break;

                    case 's':
                        flag_symbol_table = 1;
                        break;

                    case 'i':
                        flag_intermediate = 1;
                        break;  

                    case 'p':
                        flag_step1_only = 1;
                        break;         

                    default:
                        printf("-%c illegal command line option\n\n", *str);
                        print_error_message();
                        exit(-1);
                        break;
                }
            }
            else{

            }
        }
    }

    init_lexer();
    yyparse();

    if(flag_step1_only == 0){
        if(!pOutputFile){

            pOutputFile = fopen("Output/out.hex", "w");

            if (!pOutputFile){
                printf("Failed to open output file!\n");
                exit(-1);
            }
        }
        generate_code();
    }

    if(flag_intermediate == 1){ 
        print_statements();
    }

    if(flag_symbol_table == 1){
        print_table();
    }

    delete_symbol_table();
    delete_statements_list();

    fclose(pSourceFile);
    fclose(pOutputFile);
    return 0;
}


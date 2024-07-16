#ifndef INSTRUCTIONSCHED_H
#define INSTRUCTIONSCHED_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REG_NUMBER              32
#define MAX_LINE_LENGTH         64
#define NO_OPCODE               -1
#define NO_OPERAND              -2

#define OP_NOP          0
#define OP_ADD          1
#define OP_SUB          2
#define OP_OR           3
#define OP_AND          4
#define OP_NOT          5
#define OP_XOR          6
#define OP_CMP          7
#define OP_RR           8
#define OP_RL           9
#define OP_MOV          10
#define OP_BXX          11
#define OP_JMP          12 
#define OP_LD           13
#define OP_LDI          14
#define OP_LDX          15
#define OP_ST           16
#define OP_STX          17
#define OP_RETI         18
#define OP_RET          19
#define OP_HLT          20

typedef enum
{
    TYPE_DIRECTIVE,
    TYPE_SINGLE,
    TYPE_REGISTERS,
    TYPE_IMMEDIATE,
    TYPE_LAST,
    TYPE_END_BLOCK
}InstructionType_et;

typedef struct
{
    InstructionType_et type;
    int mnemonic[4];
    int operands[3];  // Assuming each instruction could have up to 3 operands
    int mnemonicValue;
    int lineNum;
    char line[MAX_LINE_LENGTH];  
}Instruction_st;

typedef struct
{
    char mnemonic[5];
    int value;
}MnemonicMap;

typedef struct codeBlock
{
    char * label;
    Instruction_st * Instructions;

    int * stallPositions;
    size_t stallPositionsNum;

    int * replacePositions;
    size_t replacePositionsNum;
    bool branchFound;
    int size;
}codeBlock_st;

// Function prototypes

/**
 * @brief Retrieves the value associated with a given mnemonic.
 *
 * @param mnemonic The mnemonic to search for. It should be a null-terminated string.
 * @return The value associated with the mnemonic if found, otherwise NO_OPCODE.
 */
int getMnemonicValue(const char *mnemonic);

/**
 * @brief Checks if the given opcode corresponds to an ALU operation.
 *
 * @param opcode The opcode value to check.
 * @return true if the opcode is an ALU operation, false otherwise.
 */
bool isAluOperation(int opcode);

/**
 * @brief Parse the given line and extracts the mnemonic and operands of an instruction.
 *
 * @param line The line of code to parse.
 * @param inst Pointer to the Instruction_st structure to store the parsed information.
 */
void parseInstruction(const char *line, Instruction_st *inst);

/**
 * @brief Parse the file and separate it into blocks of code.
 *
 * @param filename The name of the source file to parse.
 * @param ppCodeBlock_st Pointer to the pointer of the code block structure to store the parsed code blocks.
 * @param totalBlocks Pointer to an integer to store the total number of code blocks.
 * @return 0 if successful, or a negative error code if an error occurred.
 */
int codeBlockDivision(const char *filename, codeBlock_st **ppCodeBlock_st, int *totalBlocks);

/**
 * @brief Find the positions for the lines with stalls.
 *
 * @param pCodeBlock_st Pointer to the code block structure.
 * @return 0 on success, or a negative error code on failure.
 */
int checkForStalls(codeBlock_st *pCodeBlock_st);

/**
 * @brief Find the positions for the lines that can be changed to avoid the stall.
 *
 * @param pCodeBlock_st Pointer to the code block structure.
 * @return 0 on success, -ENOMEM if memory reallocation fails.
 */
int checkForReplacePositions(codeBlock_st *pCodeBlock_st);

/**
 * @brief Removes excess stalls from the code block.
 *
 * @param pCodeBlock_st Pointer to the code block structure.
 */
void removeExcessStalls(codeBlock_st *pCodeBlock_st);

/**
 * @brief Generates a file with modified code blocks.
 *
 * @param destinationFilename The filename of the destination file.
 * @param pCodeBlock_st Pointer to the code block structure.
 * @return 0 on success, or a negative error code on failure.
 */
int fileGenerator(const char *destinationFilename, codeBlock_st *pCodeBlock_st);

/**
 * @brief Prints each block of code along with relevant information.
 *
 * @param pCodeBlock_st Pointer to the code block structure.
 * @param totalBlocks The total number of code blocks.
 */
void printCodeBlocks(codeBlock_st* pCodeBlock_st, int totalBlocks);

/**
 * @brief Executes the stall optimizer in the Assembly file.
 *
 * @param filename The path of the input Assembly file.
 * @param destinationFilename The path of the output file where the optimized code will be written.
 * @return 0 on success, -1 if there was an error parsing the file.
 */
int executeStallOptimization(const char *filename, const char *destinationFilename);

#endif // OPTIMIZATION_H

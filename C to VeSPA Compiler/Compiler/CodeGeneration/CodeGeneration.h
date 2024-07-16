#ifndef ROCKETC_CODEGENERATION_H
#define ROCKETC_CODEGENERATION_H

#include "../Util/TreeNode.h"
#include "CodeGenerationTypes.h"

#define MAX_32BIT_RANGE  0xFFFFFFFF
#define MAX_IMMED_ALU   ((1 << 16) - 1)
#define MAX_IMMED_LD    ((1 << 22) - 1)
#define MAX_IMMED_LDI   ((1 << 22) - 1)
#define MAX_IMMED_LDX   ((1 << 17) - 1)
#define MAX_IMMED_ST    ((1 << 22) - 1)
#define MAX_IMMED_STX   ((1 << 17) - 1)

#define STACK_START_ADDR 1023

#define INSTRUCTION(x) (instructionLut[(x)])
#define REGISTER(x) (regNameLut[(x)])
#define L_CHILD_TYPE(p) ((p)->pChilds[0].nodeType)
#define R_CHILD_TYPE(p) ((p)->pChilds[1].nodeType)
#define NODE_TYPE(p) ((p)->nodeType)
#define NODE_OP_TYPE(p) ((p)->nodeData.dVal)
#define NODE_CHILD_NUM(p) ((p)->childNumber)

#define L_CHILD_DVAL(p) ((p)->pChilds[0].nodeData.dVal)
#define R_CHILD_DVAL(p) ((p)->pChilds[1].nodeData.dVal)
#define NODE_DVAL(p) ((p)->nodeData.dVal)

#define L_CHILD_MEM_LOC(p) ((p)->pChilds[0].pSymbol->symbolContent_u.memoryLocation)
#define R_CHILD_MEM_LOC(p) ((p)->pChilds[1].pSymbol->symbolContent_u.memoryLocation)
#define NODE_MEM_LOC(p) ((p)->pSymbol->symbolContent_u.memoryLocation)

#define L_CHILD_OP_TYPE(p) ((OperatorType_et)((p)->pChilds[0].nodeData.dVal))
#define R_CHILD_OP_TYPE(p) ((OperatorType_et)((p)->pChilds[1].nodeData.dVal))

#define L_CHILD(p) ((p)->pChilds[0])
#define R_CHILD(p) ((p)->pChilds[1])
#define VALID_ALU_IMMED(x) ((x) <= MAX_IMMED_ALU)
#define VALID_LDI_IMMED(x) ((x) <= MAX_IMMED_LDI)
#define VALID_LD_IMMED(x) ((x) <= MAX_IMMED_LD)
#define VALID_ST_IMMED(x) ((x) <= MAX_IMMED_ST)
#define IS_IN_32BIT_RANGE(x) ((x) <= MAX_32BIT_RANGE)

#define IS_TERMINAL_NODE(x) (((x) == NODE_IDENTIFIER) || ((x) == NODE_INTEGER) || ((x) == NODE_CHAR) || ((x) == NODE_FLOAT) || ((x) == NODE_POINTER_CONTENT) || ((x) == NODE_REFERENCE) || ((x) == NODE_POST_INC) || ((x) == NODE_POST_DEC) || ((x) == NODE_PRE_INC) || ((x) == NODE_PRE_DEC) || ((x) == NODE_ARRAY_INDEX || (x) == NODE_FUNCTION_CALL))
#define IS_ALU_OPERATION(x) (((x) == OP_PLUS) || ((x) == OP_MINUS) || ((x) == OP_RIGHT_SHIFT) || ((x) == OP_LEFT_SHIFT) || ((x) == OP_MULTIPLY) || ((x) == OP_DIVIDE) || ((x) == OP_REMAIN) || ((x) == OP_BITWISE_AND) || ((x) == OP_BITWISE_NOT) || ((x) == OP_BITWISE_OR) || ((x) == OP_BITWISE_XOR))
#define IS_ASSIGN_OPERATION(x) (((x) == OP_ASSIGN) || ((x) == OP_PLUS_ASSIGN) || ((x) == OP_MINUS_ASSIGN) || ((x) == OP_LEFT_SHIFT_ASSIGN) || ((x) == OP_RIGHT_SHIFT_ASSIGN) || ((x) == OP_BITWISE_AND_ASSIGN) || ((x) == OP_BITWISE_OR_ASSIGN) || ((x) == OP_BITWISE_XOR_ASSIGN) || ((x) == OP_MULTIPLY_ASSIGN) || ((x) == OP_DIVIDE_ASSIGN) || ((x) == OP_MODULUS_ASSIGN))
#define IS_BOOLEAN_OPERATION(x) (((x) == OP_GREATER_THAN) || ((x) == OP_LESS_THAN_OR_EQUAL) || ((x) == OP_GREATER_THAN_OR_EQUAL) || ((x) == OP_LESS_THAN) || ((x) == OP_EQUAL) || ((x) == OP_NOT_EQUAL) || ((x) == OP_LOGICAL_AND) || ((x) == OP_LOGICAL_OR) || ((x) == OP_LOGICAL_NOT))
#define IS_CONDITIONAL_NODE(x) (((x) == NODE_WHILE) || ((x) == NODE_CASE) || ((x) == NODE_DO_WHILE) || ((x) == NODE_IF) || ((x) == NODE_RETURN) || ((x) == NODE_FUNCTION_CALL))

#define LABEL(x) (labelLut[x])

#define TRACE_CODE

typedef struct
{
    reg_et regName;
    bool isFree;
} reg_state_st;

typedef struct
{
    OperatorType_et operatorType;
    OperatorType_et assignOpType;
    asm_instr_et asmInstruction;
} operator_pair_st;



/*
* FUNCTION PROTOTYPES
*/
static int emitMemoryInstruction(asm_instr_et instructionType, reg_et reg, reg_et idx, uint32_t dVal, char* Label);

static int emitAluInstruction(asm_instr_et instructionType, uint8_t isImed, uint32_t imedValue, reg_et resultReg, reg_et leftOperand, reg_et rightOperand);

static int emitJumpInstruction(asm_instr_et instructionType, reg_et dReg, reg_et lReg, uint32_t dVal);

static int releaseReg(reg_et reg);

static reg_et getNextAvailableReg();

static void push(reg_et reg);

static void pop(reg_et reg);

static int parseNode(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited);

static int generateCode(TreeNode_st *pTreeNode);

static int generateMultiplication();

static int generateDivision();

static int generateInitCode();

int executeCodeGeneration(TreeNode_st *pTreeRoot, FILE* pDestStream);

void codeGenerationTestUnit();

void functionGenerationTestUnit();

static int loadImm32(uint32_t dVal, reg_et destReg);

#endif

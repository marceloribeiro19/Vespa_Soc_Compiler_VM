#include <errno.h>
#include "../Util/TreeNode.h"

#ifndef ROCKETC_CODEGENERATIONTYPES_H
#define ROCKETC_CODEGENERATIONTYPES_H

typedef enum
{
    INST_ADD = 0x00,
    INST_SUB,
    INST_OR,
    INST_AND,
    INST_NOT,
    INST_XOR,
    INST_RR,
    INST_RL,
    INST_CMP,
    INST_BGT,
    INST_BLE,
    INST_BGE,
    INST_BLT,
    INST_BEQ,
    INST_BNE,
    INST_BRA,
    INST_BCC,
    INST_BVC,
    INST_BPL,
    INST_BNV,
    INST_BCS,
    INST_BVS,
    INST_BMI,
    INST_JMP,
    INST_JMPL,
    INST_LD,
    INST_LDI,
    INST_LDX,
    INST_ST,
    INST_STX,
    INST_RETI,
    INST_HALT,
    INST_NOP,
    INST_MOV
}asm_instr_et;

static const char* instructionLut[] =
{
    "ADD",
    "SUB",
    "OR",
    "AND",
    "NOT",
    "XOR",
    "RR",
    "RL",
    "CMP",
    "BGT",
    "BLE",
    "BGE",
    "BLT",
    "BEQ",
    "BNE",
    "BRA",
    "BCC",
    "BVC",
    "BPL",
    "BNV",
    "BCS",
    "BVS",
    "BMI",
    "JMP",
    "JMPL",
    "LD",
    "LDI",
    "LDX",
    "ST",
    "STX",
    "RETI",
    "HALT",
    "NOP",
    "MOV"
};

typedef enum
{
    REG_R0 = 0x00,
    REG_R1,
    REG_R2,
    REG_R3,
    REG_R4,
    REG_R5,
    REG_R6,
    REG_R7,
    REG_R8,
    REG_R9,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15,
    REG_R16,
    REG_R17,
    REG_R18,
    REG_R19,
    REG_R20,
    REG_R21,
    REG_R22,
    REG_R23,
    REG_R24,
    REG_R25,
    REG_R26,
    REG_R27,
    REG_R28,
    REG_R29,
    REG_R30,
    REG_R31,
    REG_NONE
}reg_et;

static const char* regNameLut[] =
{
    "R0",
    "R1",
    "R2",
    "R3",
    "R4",
    "R5",
    "R6",
    "R7",
    "R8",
    "R9",
    "R10",
    "R11",
    "R12",
    "R13",
    "R14",
    "R15",
    "R16",
    "R17",
    "R18",
    "R19",
    "R20",
    "R21",
    "R22",
    "R23",
    "R24",
    "R25",
    "R26",
    "R27",
    "R28",
    "R29",
    "R30",
    "R31",
    "REG_NONE"
};

typedef enum
{
    WHILE_START       = 0x00,
    WHILE_EXIT        = 0x01,
    TRUE              = 0x02,
    FALSE             = 0x03,
    SKIP              = 0x04,
    CASE              = 0x05,
    CASE_EXIT         = 0x06,
    DEFAULT           = 0x07,
    IF_FALSE          = 0x08,
    IF_EXIT           = 0x09,
    FUNCTION_NAME     = 0x0A,
    FUNCTION_MUL      = 0x0B,
    FUNCTION_DIV      = 0x0C,
    SKIP_MUL_ADD_BIT  = 0x0D,
    SKIP_DIV_BIT,

    LABEL_MAX         
    
    
}label_et;

static const char* labelLut[] =
{
    "WHILE_START_",
    "WHILE_EXIT_",
    "TRUE_",
    "FALSE_",
    "SKIP_",
    "CASE_",
    "CASE_EXIT_",
    "DEFAULT_",
    "IF_FALSE_",
    "IF_EXIT_",
    "FUNCTION_",
    "FUNCTION_MUL",
    "FUNCTION_DIV",
    "SKIP_MUL_ADD_BIT_",
    "SKIP_DIV_BIT_",
    
};

#endif

#ifndef _ASM_OPERATIONS_H_
#define _ASM_OPERATIONS_H_


//basic instructions opcodes
#define NOP_OPCODE      0
#define ADD_OPCODE      1
#define SUB_OPCODE      2
#define OR_OPCODE       3
#define AND_OPCODE      4
#define NOT_OPCODE      5
#define XOR_OPCODE      6
#define CMP_OPCODE      7
#define BXX_OPCODE      8
#define JMP_OPCODE      9
#define LD_OPCODE       10
#define LDI_OPCODE      11
#define LDX_OPCODE      12
#define ST_OPCODE       13
#define STX_OPCODE      14
#define RR_OPCODE       15
#define RL_OPCODE       16
#define HLT_OPCODE      31

//extra instructions opcodes
#define RETI_OPCODE     17

//branch conditions
#define BRA_COND        0
#define BCC_COND        1
#define BVC_COND        2
#define BEQ_COND        3
#define BGE_COND        4
#define BGT_COND        5
#define BPL_COND        6
#define BNV_COND        8
#define BCS_COND        9
#define BVS_COND        10
#define BNE_COND        11
#define BLT_COND        12
#define BLE_COND        13
#define BMI_COND        14

//directives
#define DOT_BYTE_OP     40
#define DOT_WORD_OP     41
#define DOT_ALLOC_OP    42
#define DOT_ORG_OP      43


#endif
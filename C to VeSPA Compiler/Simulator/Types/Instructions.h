#ifndef ROCKETSIM_INSTRUCTION_H
#define ROCKETSIM_INSTRUCTION_H

typedef enum
{
    OP_NOP  = 0b00000,
    OP_ADD  = 0b00001,
    OP_SUB  = 0b00010,
    OP_OR   = 0b00011,
    OP_AND  = 0b00100,
    OP_NOT  = 0b00101,
    OP_XOR  = 0b00110,
    OP_CMP  = 0b00111,
    OP_BXX  = 0b01000,
    OP_JMP  = 0b01001,
    OP_LD   = 0b01010,
    OP_LDI  = 0b01011,
    OP_LDX  = 0b01100,
    OP_ST   = 0b01101,
    OP_STX  = 0b01110,
    OP_HALT = 0b11111
}opcode_et;


#endif

`ifndef CONSTANTS_V
`define CONSTANTS_V

`define BUS_WIDTH       32
`define BUS_MSB         31

`define PC_SEL_WIDTH    3
`define PC_SEL_MSB      2

`define RET_REG         1
`define RETI_REG        1

`define PC_SEL_BXX      0
`define PC_SEL_JMP      1
`define PC_SEL_RET      2
`define PC_SEL_RETI     3
`define PC_SEL_INT      4
`define PC_SEL_ADD4     5

`define REG_FILE_SIZE   31
`define REG_FILE_WIDTH  5
`define REG_FILE_MSB    4

`define OPCODE_WIDTH    5
`define OPCODE_MSB      4

`define ALU_SEL_WIDTH   3
`define ALU_SEL_MSB     2

`define OP_NOP          5'd0
`define OP_ADD          5'd1
`define OP_SUB          5'd2
`define OP_OR           5'd3
`define OP_AND          5'd4
`define OP_NOT          5'd5
`define OP_XOR          5'd6
`define OP_CMP          5'd7
`define OP_BXX          5'd8
`define OP_JMP          5'd9
`define OP_LD           5'd10
`define OP_LDI          5'd11
`define OP_LDX          5'd12
`define OP_ST           5'd13
`define OP_STX          5'd14
`define OP_RETI         5'd17
`define OP_RET          5'd18
`define OP_HLT          5'd31

`define RF_SEL_WIDTH    2
`define RF_SEL_MSB      1

`define RF_SEL_RS2      0
`define RF_SEL_RST      1
`define RF_SEL_RET      2
`define RF_SEL_RETI     2

`define RF_IN_SEL_WIDTH 2
`define RF_IN_SEL_MSB   1

`define RF_IN_MEM_OUT   0
`define RF_IN_PC        1
`define RF_IN_ALU       2
`define RF_IN_IMM       3

`define MEM_SEL_IMM     0
`define MEM_SEL_OPX     1

`define PC_INC          4

`define CCODES_WIDTH    4
`define CCODES_MSB      3

`define CCODE_CARRY     3
`define CCODE_ZERO      2   
`define CCODE_NEG       1   
`define CCODE_OVF       0   

`define ISR1_ADDRESS    4
`define ISR2_ADDRESS    8
`define ISR3_ADDRESS    12
`define ISR4_ADDRESS    16


`endif
`timescale 1ns / 1ps

`include "Constants.v"

/// \input i_Clk Source Clock signal for the slave device, logic is processed on rising edges of this signal
/// \input i_Rst Reset signal for the module, active high
/// \input i_InstructionRegister Current instruction
/// \input i_Read2_Addr Choose the second address to read from the register file
/// \input i_We_rf Enable Write into Register File 
/// \input i_RfWrAddr Address to write into Register File
/// \input i_W_dataIn Data to be writen int o Register File
/// \output o_Opcode opcode from the current instruction to control unit decide the control signals required
/// \output o_ImmOp bit 16 from current instruction send to control unit, indicate if will use a immediate value or not 
/// \output o_IrRs2 output from hazard unit (forwarding) to indicate the first register will be read
/// \output o_IrRs1 output from hazard unit (forwarding) to indicate the second register will be read
/// \output o_IrRst output to indicate the address that will be written to the register file at the write back stage
/// \output o_R1Out value read from output A of the register file
/// \output o_R2Out value read from output B of the register file
/// \output o_Imm16 extended signal from the first 16 bits
/// \output o_Imm17 extended signal from the first 17 bits
/// \output o_Imm22 extended signal from the first 22 bits
/// \output o_Imm23 extended signal from the first 23 bits
/// \output o_BranchCond condition to test in Branch

module InstructionDecode
(
    input i_Clk,
    input i_Rst,
    input [`BUS_MSB:0] i_InstructionRegister,
    input [`RF_SEL_MSB:0] i_Read2AddrSel,
    input i_RfWe,
    input [4:0] i_RfWrAddr,
    input [`BUS_MSB:0] i_RfDataIn,
    
    output [4:0] o_Opcode,         //output to CU 
    output o_ImmOp,                //output to CU  

    //hazard signals
    output [4:0] o_IrRs2,          //R2_Addr
    output [4:0] o_IrRs1,          //R1_Addr
        
    output [4:0] o_IrRst,          //IR_RDST
    output [`BUS_MSB:0] o_R1Out,   //RF_Read1
    output [`BUS_MSB:0] o_R2Out,   //RF_Read2
    output [`BUS_MSB:0] o_Imm16,
    output [`BUS_MSB:0] o_Imm17,
    output [`BUS_MSB:0] o_Imm22,
    output [`BUS_MSB:0] o_Imm23,

    output [3:0] o_BranchCond
);


wire [4:0] w_IrRs1;     //IR_RS1 [21:17]
wire [4:0] w_IrRs2;     //IR_RS2 [15:11]
wire [4:0] w_IrRst;     //IR_RST [26:22]

wire [4:0] w_IrRs2_in;

wire [15:0] w_Imm16;
wire [16:0] w_Imm17;
wire [21:0] w_Imm22;
wire [22:0] w_Imm23;


assign o_IrRs1 = w_IrRs1;
assign o_IrRs2 = w_IrRs2_in;
assign o_IrRst = w_IrRst;

//Decode IR Register
assign w_IrRs1 = i_InstructionRegister[21:17];
assign w_IrRs2 = i_InstructionRegister[15:11];
assign w_IrRst = i_InstructionRegister[26:22];

assign w_Imm16 = i_InstructionRegister[15:0];
assign w_Imm17 = i_InstructionRegister[16:0];
assign w_Imm22 = i_InstructionRegister[21:0];
assign w_Imm23 = i_InstructionRegister[22:0];

assign o_BranchCond = i_InstructionRegister[26:23];
assign o_ImmOp = i_InstructionRegister[16];
assign o_Opcode = i_InstructionRegister[31:27];


//Sign-Extends
assign o_Imm16 = {16'b0, w_Imm16};
assign o_Imm17 = {15'b0, w_Imm17};
assign o_Imm22 = {10'b0, w_Imm22};
assign o_Imm23 = {9'b0, w_Imm23};


    
assign w_IrRs2_in = (i_Read2AddrSel == 2'b00) ? w_IrRs2 :               //w_IrRs2_in is the read adress B to register file after the mux i_Read2AddrSel
                    (i_Read2AddrSel == 2'b01) ? w_IrRst : `RET_REG;


RegisterFile rf
(
    .i_Clk(i_Clk),
    .i_Rst(i_Rst),
    .i_WrEnable(i_RfWe),
    .i_DataIn(i_RfDataIn),
    .i_WrAddr(i_RfWrAddr),
    .i_RdAddrA(w_IrRs1),
    .i_RdAddrB(w_IrRs2_in),
    .o_DataOutA(o_R1Out),
    .o_DataOutB(o_R2Out)
);

                                   
endmodule

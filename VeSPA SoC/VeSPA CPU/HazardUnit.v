`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2024 11:49:19 PM
// Design Name: 
// Module Name: hazard_unit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

//Defined in Constants.v
`define REG_FILE_MSB    4
`define ALU_OP_MSB      1

`include "Constants.v"

module HazardUnit
(
    input i_Clk,
    input i_Rst,
    //control hazards inputs
    input [`REG_FILE_MSB:0] i_IrRead1AddrDec,
    input [`REG_FILE_MSB:0] i_IrRead2AddrDec,
    input [`REG_FILE_MSB:0] i_RfReadDstExec,
    input i_BranchVerification,
    input i_BranchBit,
    input i_JmpBit,
    input i_RetiBit,
    input i_RdMemExe,
    input i_WeMemEnable,
    input i_AluEnDec,
    input i_InterruptSignal,
    
    //control hazards outputs
    output o_FlushFetch,
    output o_FlushDecode,
    output o_FlushExecute,
    output o_FlushMemory,
    output o_StallSignal,

    //forward unit inputs
    input [`REG_FILE_MSB:0] i_IrRead1AddrDecodeExec,
    input [`REG_FILE_MSB:0] i_IrRead2AddrDecodeExec,
    input i_RfWeMemory,
    input i_RfWeWriteBack,
    input [`REG_FILE_MSB:0] i_RfReadDstMemory,
    input [`REG_FILE_MSB:0] i_RfReadDstWriteBack,
    input [`RF_IN_SEL_MSB:0] i_RfDataInSelMem,                       //este mux vai fazer a distinção entre o LDI e as operações da ALU, suprimindo a possível necessidade de um bit de destinção
    
    //forward unit outputs
    output [`ALU_OP_MSB:0]o_ForwardOp1,
    output [`ALU_OP_MSB:0]o_ForwardOp2
    );
    
    
    control_hazards CTRL_HZRD (
    .i_Clk(i_Clk),
    .i_Rst(i_Rst),
    .i_IrRead1AddrDec(i_IrRead1AddrDec),
    .i_IrRead2AddrDec(i_IrRead2AddrDec),
    .i_RfReadDstExec(i_RfReadDstExec),
    .i_BranchVerification(i_BranchVerification),
    .i_BranchBit(i_BranchBit),
    .i_JmpBit(i_JmpBit),
    .i_RetiBit(i_RetiBit),
    .i_AluEnDec(i_AluEnDec),
    .i_RdMemExe(i_RdMemExe),
    .i_WeMemEnable(i_WeMemEnable),
    .i_InterruptSignal(i_InterruptSignal),
    .o_FlushFetch(o_FlushFetch),
    .o_FlushDecode(o_FlushDecode),
    .o_FlushExecute(o_FlushExecute),
    .o_FlushMemory(o_FlushMemory),
    .o_StallSignal(o_StallSignal)
    );
    
    
    forwarding_unit FWD_UNIT(
//    .i_Clk(i_Clk),
//    .i_Rst(i_Rst),
    .i_IrRead1AddrDecodeExec(i_IrRead1AddrDecodeExec),
    .i_IrRead2AddrDecodeExec(i_IrRead2AddrDecodeExec),
    .i_RfWeMemory(i_RfWeMemory),
    .i_RfWeWriteBack(i_RfWeWriteBack),
    .i_RfReadDstMemory(i_RfReadDstMemory),
    .i_RfReadDstWriteBack(i_RfReadDstWriteBack),
    .i_RfDataInSelMem(i_RfDataInSelMem),
    .o_ForwardOp1(o_ForwardOp1),
    .o_ForwardOp2(o_ForwardOp2)
    
    );
    
endmodule
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/26/2024 12:16:42 AM
// Design Name: 
// Module Name: forwarding_unit
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

module forwarding_unit(

    input [`REG_FILE_MSB:0] i_IrRead1AddrDecodeExec,    //RF READ ADDRESS 1
    input [`REG_FILE_MSB:0] i_IrRead2AddrDecodeExec,    //RF READ ADDRESS 2
    input i_RfWeMemory,                                 //RF ENABLE MEM STAGE
    input i_RfWeWriteBack,                              //RF ENABLE EXE STAGE
    input [`REG_FILE_MSB:0] i_RfReadDstMemory,          //RF WRITE ADDRESS MEM STAGE
    input [`REG_FILE_MSB:0] i_RfReadDstWriteBack,       //RF WRITE ADDRESS WB STAGE
    input [`RF_IN_SEL_MSB:0] i_RfDataInSelMem,           //mux will indicate if is ALU or LDI instruction - EX/MEM RF
    
    output [`ALU_OP_MSB:0] o_ForwardOp1,
    output [`ALU_OP_MSB:0] o_ForwardOp2
    );
            
    assign o_ForwardOp1 =  ((i_IrRead1AddrDecodeExec == i_RfReadDstMemory) && i_RfWeMemory && (i_RfDataInSelMem == 2'b10)) ? 2'b01 : //alu mem
                           ((i_IrRead1AddrDecodeExec == i_RfReadDstMemory) && i_RfWeMemory && (i_RfDataInSelMem == 2'b11)) ? 2'b11 : //ldi mem
                           ((i_IrRead1AddrDecodeExec == i_RfReadDstWriteBack) && i_RfWeWriteBack) ? 2'b10 : 2'b00; //alu or ldi wb                         
                           
    assign o_ForwardOp2 =  ((i_IrRead2AddrDecodeExec == i_RfReadDstMemory) && i_RfWeMemory && (i_RfDataInSelMem == 2'b10)) ? 2'b01 : //alu mem
                           ((i_IrRead2AddrDecodeExec == i_RfReadDstMemory) && i_RfWeMemory && (i_RfDataInSelMem == 2'b11)) ? 2'b11 : //ldi mem
                           ((i_IrRead2AddrDecodeExec == i_RfReadDstWriteBack) && i_RfWeWriteBack) ? 2'b10 : 2'b00;    

endmodule
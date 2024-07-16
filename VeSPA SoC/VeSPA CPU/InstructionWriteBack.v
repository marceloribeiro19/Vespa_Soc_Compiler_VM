`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2024 02:00:36 PM
// Design Name: 
// Module Name: InstructionWriteBack
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

`include "Constants.v"

module InstructionWriteBack(

    input i_Clk,
    input i_Rst,
    input [`BUS_MSB:0] i_AluOut,
    input [`BUS_MSB:0] i_Imm22,
    input [`BUS_MSB:0] i_DataMem,
    input [`BUS_MSB:0] i_ProgramCounter,

    input [1:0] i_RfDataInSel,
    
    input i_InterruptSignal,

    output [`BUS_MSB:0] o_RfData

    );

    assign  o_RfData = (i_RfDataInSel == 2'b00) ? i_DataMem : 
                       (i_RfDataInSel == 2'b01) ? i_ProgramCounter :
                       (i_RfDataInSel == 2'b10) ? i_AluOut : i_Imm22;
                      
endmodule

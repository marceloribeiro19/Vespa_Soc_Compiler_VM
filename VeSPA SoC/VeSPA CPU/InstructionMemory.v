`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2024 12:10:51 AM
// Design Name: 
// Module Name: InstructionMemory
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


module InstructionMemory
(

input i_Clk,
input i_Rst,
    
input [`BUS_MSB:0] i_Imm22,
input [`BUS_MSB:0] i_ImmOpX,

//ControlUnit
input i_MemAddrSel,

output [`BUS_MSB:0] o_dataMemAddress

);

assign o_dataMemAddress = (i_MemAddrSel == 1'b0) ? i_Imm22 : i_ImmOpX;

endmodule

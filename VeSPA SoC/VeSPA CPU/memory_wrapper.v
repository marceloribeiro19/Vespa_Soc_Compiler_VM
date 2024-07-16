`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2024 12:14:52 AM
// Design Name: 
// Module Name: memory_wrapper
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


module memory_wrapper(
    //Bus related signals
    input i_Clk,
    input i_Rst,
    input i_WEnable,
    input [31:0] i_WAddr,
    input [31:0] i_WData,
    input i_REnable,
    input [31:0] i_RAddr,
    output [31:0] o_RData,
    output reg o_Err,
    //User signals begin here
    output o_MemBusy
);

wire [31:0] w_MemAddr;
wire [3:0] w_WEnA;
wire w_RstA, w_RstB;

assign w_MemAddr = i_WEnable ? i_WAddr : i_REnable ? i_RAddr : 0;
assign w_WEnA = {i_WEnable, i_WEnable, i_WEnable, i_WEnable};

RAM _Bram(
  .clka(i_Clk),
  .rsta(i_Rst),
  .wea(w_WEnA),
  .addra(w_MemAddr),
  .dina(i_WData),
  .douta(o_RData),
  .rsta_busy(o_MemBusy)
);

endmodule

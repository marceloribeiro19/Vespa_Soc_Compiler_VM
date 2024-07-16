`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/24/2024 07:38:21 PM
// Design Name: 
// Module Name: tb_ps2
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


module tb_ps2(

    );
    
    reg i_Clk;
    reg i_Rst;
    reg i_WEnable;
    reg [31:0] i_WAddr;
    reg [31:0] i_WData;
    reg i_REnable;
    reg [31:0] i_RAddr;
    wire [31:0] o_RData;
    wire o_Err;

    reg PS2C;                     // clock signal from PS2 peripheral
    reg PS2D;                     // bit read from PS2 peripheral
     
    custom_ps2_interface ps2_interface(

     .i_Clk(i_Clk),
     .i_Rst(i_Rst),
     .i_WEnable(i_WEnable),
     .i_WAddr(i_WAddr),
     .i_WData(i_WData),
     .i_REnable(i_REnable),
     .i_RAddr(i_RAddr),
     .o_RData(o_RData),
     .o_Err(o_Err),
     .PS2C(PS2C),                     // clock signal from PS2 peripheral
     .PS2D(PS2D)                     // bit read from PS2 peripheral
);
    
    initial begin
    
    i_Clk = 0;
    i_Rst = 1;
    i_WAddr = 0;
    i_WData = 0;
    i_WEnable = 0;
    i_RAddr = 0;

    #10
    
    i_Rst = 0;
    i_WEnable = 1;
    i_WData = 32'd1;
    
    #20
    
    i_WEnable = 0;
    i_REnable = 1;

    end
    
    
    
    always #4 i_Clk = ~i_Clk;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
endmodule

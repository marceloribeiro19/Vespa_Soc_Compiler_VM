`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2024 10:42:57 PM
// Design Name: 
// Module Name: CustomInterconnect
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

`define BUS_WIDTH   32

module CustomInterconnect(
    input i_Clk, 
    input i_Rst, 
    
    input i_WEnable, 
    input [`BUS_WIDTH-1:0]i_WAddr,
    input [`BUS_WIDTH-1:0]i_WData,
    input i_REnable, 
    input [`BUS_WIDTH-1:0]i_RAddr,
    output [`BUS_WIDTH-1:0]o_RData, 

    output o_WEnable_0, 
    output [`BUS_WIDTH-1:0]o_WAddr_0,
    output [`BUS_WIDTH-1:0]o_WData_0,
    output o_REnable_0, 
    output [`BUS_WIDTH-1:0]o_RAddr_0,
    input [`BUS_WIDTH-1:0]i_RData_0, 

    output o_WEnable_1, 
    output [`BUS_WIDTH-1:0]o_WAddr_1,
    output [`BUS_WIDTH-1:0]o_WData_1,
    output o_REnable_1, 
    output [`BUS_WIDTH-1:0]o_RAddr_1,
    input [`BUS_WIDTH-1:0]i_RData_1, 
    
    output o_WEnable_2, 
    output [`BUS_WIDTH-1:0]o_WAddr_2,
    output [`BUS_WIDTH-1:0]o_WData_2,
    output o_REnable_2, 
    output [`BUS_WIDTH-1:0]o_RAddr_2,
    input [`BUS_WIDTH-1:0]i_RData_2, 
    
    output o_WEnable_3, 
    output [`BUS_WIDTH-1:0]o_WAddr_3,
    output [`BUS_WIDTH-1:0]o_WData_3,
    output o_REnable_3,
    output [`BUS_WIDTH-1:0]o_RAddr_3,
    input [`BUS_WIDTH-1:0]i_RData_3, 
    
    output o_WEnable_4,
    output [`BUS_WIDTH-1:0]o_WAddr_4,
    output [`BUS_WIDTH-1:0]o_WData_4,
    output o_REnable_4, 
    output [`BUS_WIDTH-1:0]o_RAddr_4,
    input [`BUS_WIDTH-1:0]i_RData_4,
    
    output o_WEnable_5,
    output [`BUS_WIDTH-1:0]o_WAddr_5,
    output [`BUS_WIDTH-1:0]o_WData_5,
    output o_REnable_5,
    output [`BUS_WIDTH-1:0]o_RAddr_5,
    input [`BUS_WIDTH-1:0]i_RData_5,  
    
    output o_WEnable_6, 
    output [`BUS_WIDTH-1:0]o_WAddr_6,
    output [`BUS_WIDTH-1:0]o_WData_6,
    output o_REnable_6,
    output [`BUS_WIDTH-1:0]o_RAddr_6,
    input [`BUS_WIDTH-1:0]i_RData_6,
    
    output o_WEnable_7, 
    output [`BUS_WIDTH-1:0]o_WAddr_7,
    output [`BUS_WIDTH-1:0]o_WData_7,
    output o_REnable_7,
    output [`BUS_WIDTH-1:0]o_RAddr_7,
    input [`BUS_WIDTH-1:0]i_RData_7
    );
    
    reg [`BUS_WIDTH-1:0]r_RAddr;
    
    //slave 0 interface -> data memory 1 kByte
    assign o_WEnable_0  = (i_WAddr[10] == 1'b0) ? i_WEnable : 1'bZ;
    assign o_WAddr_0    = (i_WAddr[10] == 1'b0) ? i_WAddr   : 32'bZ;
    assign o_WData_0    = (i_WAddr[10] == 1'b0) ? i_WData   : 32'bZ;
    assign o_REnable_0  = (i_RAddr[10] == 1'b0) ? i_REnable : 1'bZ;
    assign o_RAddr_0    = (i_RAddr[10] == 1'b0) ? i_RAddr   : 32'bZ;
    
    //slave 1 interface -> 4 registers    
    assign o_WEnable_1  = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b000) ? i_WEnable              : 1'bZ;
    assign o_WAddr_1    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b000) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_1    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b000) ? i_WData                : 32'bZ;
    assign o_REnable_1  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b000) ? i_REnable              : 1'bZ;
    assign o_RAddr_1    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b000) ? {30'b0,i_RAddr[1:0]}   : 32'bZ;
    
    //slave 2 interface -> 4 registers
    assign o_WEnable_2  = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b001) ? i_WEnable              : 1'bZ;
    assign o_WAddr_2    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b001) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_2    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b001) ? i_WData                : 32'bZ;
    assign o_REnable_2  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b001) ? i_REnable              : 1'bZ;
    assign o_RAddr_2    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b001) ? {30'b0,i_RAddr[1:0]}   : 32'bZ;  
    
    //slave 3 interface -> 4 registers
    assign o_WEnable_3  = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b010) ? i_WEnable              : 1'bZ;
    assign o_WAddr_3    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b010) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_3    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b010) ? i_WData                : 32'bZ;
    assign o_REnable_3  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b010) ? i_REnable              : 1'bZ;
    assign o_RAddr_3    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b010) ? {30'b0,i_RAddr[1:0]}   : 32'bZ; 
    
    //slave 4 interface -> 4 registers
    assign o_WEnable_4  = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b011) ? i_WEnable              : 1'bZ;
    assign o_WAddr_4    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b011) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_4    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b011) ? i_WData                : 32'bZ;
    assign o_REnable_4  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b011) ? i_REnable              : 1'bZ;
    assign o_RAddr_4    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b011) ? {30'b0,i_RAddr[1:0]}   : 32'bZ;   
    
    //slave 5 interface -> 4 registers
    assign o_WEnable_5  = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b100) ? i_WEnable              : 1'bZ;
    assign o_WAddr_5    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b100) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_5    = (i_WAddr[10] == 1'b1 && i_WAddr[4:2] == 3'b100) ? i_WData                : 32'bZ;
    assign o_REnable_5  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b100) ? i_REnable              : 1'bZ;
    assign o_RAddr_5    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b100) ? {30'b0,i_RAddr[1:0]}   : 32'bZ;
    
    //slave 6 interface -> 4 registers
    assign o_WEnable_6  = (i_WAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b101) ? i_WEnable              : 1'bZ;
    assign o_WAddr_6    = (i_WAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b101) ? {30'b0,i_WAddr[1:0]}   : 32'bZ;
    assign o_WData_6    = (i_WAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b101) ? i_WData                : 32'bZ;
    assign o_REnable_6  = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b101) ? i_REnable              : 1'bZ;
    assign o_RAddr_6    = (i_RAddr[10] == 1'b1 && i_RAddr[4:2] == 3'b101) ? {30'b0,i_RAddr[1:0]}   : 32'bZ;
    
     //slave 7 interface -> 8 registers
    assign o_WEnable_7  = (i_WAddr[10] == 1'b1 && (i_RAddr[4:2] == 3'b110 || i_RAddr[4:2] == 3'b111)) ? i_WEnable              : 1'bZ;
    assign o_WAddr_7    = (i_WAddr[10] == 1'b1 && (i_RAddr[4:2] == 3'b110 || i_RAddr[4:2] == 3'b111)) ? {29'b0,i_WAddr[2:0]}   : 32'bZ;
    assign o_WData_7    = (i_WAddr[10] == 1'b1 && (i_RAddr[4:2] == 3'b110 || i_RAddr[4:2] == 3'b111)) ? i_WData                : 32'bZ;
    assign o_REnable_7  = (i_RAddr[10] == 1'b1 && (i_RAddr[4:2] == 3'b110 || i_RAddr[4:2] == 3'b111)) ? i_REnable              : 1'bZ;
    assign o_RAddr_7    = (i_RAddr[10] == 1'b1 && (i_RAddr[4:2] == 3'b110 || i_RAddr[4:2] == 3'b111)) ? {29'b0,i_RAddr[2:0]}   : 32'bZ;
    
    
    //Read data
    assign o_RData      = (r_RAddr[10] == 1'b0)                           ? i_RData_0 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b000) ? i_RData_1 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b001) ? i_RData_2 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b010) ? i_RData_3 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b011) ? i_RData_4 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b100) ? i_RData_5 :
                          (r_RAddr[10] == 1'b1 && r_RAddr[4:2] == 3'b101) ? i_RData_6 : 
                          (r_RAddr[10] == 1'b1 &&(r_RAddr[4:2] == 3'b110 || r_RAddr[4:2] == 3'b111)) ? i_RData_7 : 32'bZ;
                          
always @(posedge i_Clk) begin
    if(i_Rst) begin
        r_RAddr <= 0;
    end
    else begin
        r_RAddr <= i_RAddr;
    end
end
   
                      
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/20/2024 06:05:41 PM
// Design Name: 
// Module Name: gpio
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



module GPIO_PORT(
    
    input [7:0] direction,
    
    input [7:0] write_reg,      
    (* keep *)output [7:0] read_reg,
    
    input [3:0] pin_in,
    output [3:0] pin_out
    //antes estava inout, mas ao sintetizar dava problemas
    
);    
    
    assign pin_out[0] = direction[0] ? write_reg[0] : 1'bz;
    assign pin_out[1] = direction[1] ? write_reg[1] : 1'bz;
    assign pin_out[2] = direction[2] ? write_reg[2] : 1'bz;
    assign pin_out[3] = direction[3] ? write_reg[3] : 1'bz;
    //assign pin[4] = direction[4] ? write_reg[4] : 1'bz;
    //assign pin[5] = direction[5] ? write_reg[5] : 1'bz;
    //assign pin[6] = direction[6] ? write_reg[6] : 1'bz;
    //assign pin[7] = direction[7] ? write_reg[7] : 1'bz;
    
    
    assign read_reg = {pin_in, 4'b0};
endmodule


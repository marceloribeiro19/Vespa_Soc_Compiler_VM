`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/24/2024 07:02:06 PM
// Design Name: 
// Module Name: custom_ps2_interface
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


module custom_ps2_interface(

    input i_Clk,
    input i_Rst,
    input i_WEnable,
    input [31:0] i_WAddr,
    input [31:0] i_WData,
    input i_REnable,
    input [31:0] i_RAddr,
    output reg [31:0] o_RData,
    output reg o_Err,
    output [3:0] o_Data,

    input PS2C,                     // clock signal from PS2 peripheral
    input PS2D                     // bit read from PS2 peripheral
    
);
    
    reg ps2_enable;
    wire [7:0] ps2_key_out;
    wire error;
    
    always @(posedge i_Clk) begin
    if (i_Rst) begin
        ps2_enable = 0;
    end
    else begin
        if (i_WEnable) begin
            //Verify it the write address is within range
            case (i_WAddr)
                2'b00: begin
                    ps2_enable = i_WData[0];
                    o_Err <= 0;
                end
                default: o_Err <= 1;
            endcase
        end
        //Check if there is a read request pending
        else if (i_REnable) begin
             case (i_RAddr)
                2'b00: begin
                    o_RData <= {31'b0, ps2_enable};
                    o_Err <= 0;
                end

                2'b01: begin
                    o_RData <= {24'b0, ps2_key_out};
                    //o_RData <= {24'b0, 8'b01111001}; // 79h
                    //o_RData <= {24'b0, 8'b01111011};    // 7Bh
                    o_Err <= 0;
                end

                default: o_Err <= 1;
            endcase
        end
        else begin
            //Do nothing
        end
    end
end
    
    //assign error = o_Err;
    
ps2_new ps2 (
    .clk(i_Clk),
    .reset(i_Rst),
    .PS2_enable(ps2_enable),
    .PS2D(PS2D),
    .PS2C(PS2C),
    .o_error(error),
    .o_key(ps2_key_out),
    .o_Data(o_Data)
);
    
    
    
endmodule

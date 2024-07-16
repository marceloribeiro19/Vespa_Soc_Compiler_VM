`timescale 1ns / 1ps

`include "Constants.v"

/// \brief Register File module. This module implements a pseudo triple port register file, with two read ports and one write port that can be used simultaneously
/// \input i_Clk Source Clock signal for the slave device, logic is processed on rising edges of this signal
/// \input i_Rst Reset signal for the module, active high
/// \input i_WrEnable Write Enable signal. When this signal is pulled high, the value present on i_DataIn will be writen to the register on address i_WrAddr
module RegisterFile
(
    input i_Clk,
    input i_Rst,
    (* keep *)input i_WrEnable,
    input [`BUS_MSB:0] i_DataIn,
    input [`REG_FILE_MSB:0] i_WrAddr,
    input [`REG_FILE_MSB:0] i_RdAddrA,
    input [`REG_FILE_MSB:0] i_RdAddrB,
    output reg [`BUS_MSB:0] o_DataOutA,
    output reg [`BUS_MSB:0] o_DataOutB, 
    
    output [2:0]led_test
);

reg [(32 - 1):0] r_RegFile [`REG_FILE_SIZE:0] ;

integer i;

always @(posedge i_Clk) begin  
    if (i_Rst) begin
        for (i = 0; i < 32; i = i + 1) begin
            r_RegFile[i] <= 0;
        end
    end
    else begin
        if (i_WrEnable) begin
            r_RegFile[i_WrAddr] <= i_DataIn;
        
            if (i_RdAddrA == i_WrAddr) begin
                o_DataOutA <= i_DataIn;
            end
            else begin
                o_DataOutA <= r_RegFile[i_RdAddrA];
            end

            if (i_RdAddrB == i_WrAddr) begin
                o_DataOutB <= i_DataIn;
            end
            else begin
                o_DataOutB <= r_RegFile[i_RdAddrB];
            end
        end
        else begin
            o_DataOutA <= r_RegFile[i_RdAddrA];
            o_DataOutB <= r_RegFile[i_RdAddrB];
        end        
    end 
end

assign led_test[0] = (r_RegFile[30] == 'd10) ? 1 : 0;
assign led_test[1] = (r_RegFile[31] == 'd15) ? 1 : 0;
assign led_test[2] = (r_RegFile[29] == 'd10) ? 1 : 0;

endmodule
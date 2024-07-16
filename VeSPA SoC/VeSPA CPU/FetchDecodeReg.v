`timescale 1ns / 1ps


/// \input i_Clk Source Clock signal for the slave device, logic is processed on rising edges of this signal
/// \input i_Rst Reset signal for the module, active high
/// \input i_Stall Stall signal, stops PC and IR from changing when high
/// \input i_Flush Flush signal, reset the PC and IR in this stage

`include "Constants.v"

module FetchDecodeReg
(
    input i_Clk,
    input i_Rst,
    input [`BUS_MSB:0] i_InstructionRegister,
    input [`BUS_MSB:0] i_ProgramCounter,
    input i_Stall,
    input i_Flush,

    output reg [`BUS_MSB:0] o_InstructionRegister,
    output reg [`BUS_MSB:0] o_ProgramCounter
);

    always @(posedge i_Clk) begin 
        if(i_Rst || i_Flush) begin
            o_InstructionRegister   <= 0;
            o_ProgramCounter        <= 0;
        end
        else begin
            if(i_Stall) begin
                o_InstructionRegister   <= o_InstructionRegister; 
                o_ProgramCounter        <= o_ProgramCounter;
            end
            else begin
                o_InstructionRegister   <= i_InstructionRegister;
                o_ProgramCounter        <= i_ProgramCounter;
            end
        end

    end

endmodule

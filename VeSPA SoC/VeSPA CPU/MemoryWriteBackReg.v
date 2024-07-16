`timescale 1ns / 1ps

`include "Constants.v"

module MemoryWriteBackReg
(   
    input i_Clk,
    input i_Rst,
    input i_Stall,
    //input i_Flush,

    input [`BUS_MSB:0] i_ProgramCounter,
    input [4:0] i_IrRst,                      //IR_RDST 
    input [`BUS_MSB:0] i_AluOut,
    input [`BUS_MSB:0] i_Imm22,
    
    input i_WrEnRf,
    input [1:0] i_RfDataInSel,
    


    output reg [`BUS_MSB:0] o_ProgramCounter,
    output reg [4:0] o_IrRst,                  //IR_RDST 
    output reg [`BUS_MSB:0] o_AluOut,
    output reg [`BUS_MSB:0] o_Imm22,

    output reg o_WrEnRf,
    output reg [1:0] o_RfDataInSel
     
);
    
always @(posedge i_Clk) begin
    if (i_Rst) begin
        o_ProgramCounter <= 0;
        o_IrRst          <= 0;
        o_AluOut         <= 0;
        o_Imm22          <= 0;
        o_WrEnRf         <= 0;
        o_RfDataInSel    <= 0;
    end
    else begin
        if (i_Stall) begin                
            o_ProgramCounter <= o_ProgramCounter;
            o_IrRst          <= o_IrRst;
            o_AluOut         <= o_AluOut;
            o_Imm22          <= o_Imm22;
            o_WrEnRf         <= o_WrEnRf;
            o_RfDataInSel    <= o_RfDataInSel;
        end
        else begin
            o_ProgramCounter <= i_ProgramCounter;
            o_IrRst          <= i_IrRst;
            o_AluOut         <= i_AluOut;
            o_Imm22          <= i_Imm22;
            o_WrEnRf         <= i_WrEnRf;
            o_RfDataInSel    <= i_RfDataInSel;
            
        end
    end
end  


endmodule

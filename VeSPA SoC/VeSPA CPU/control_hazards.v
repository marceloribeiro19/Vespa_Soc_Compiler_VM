`timescale 1ns / 1ps

`include "Constants.v"

module control_hazards
(
    input i_Clk,
    input i_Rst,
    input [`REG_FILE_MSB:0] i_IrRead1AddrDec,
    input [`REG_FILE_MSB:0] i_IrRead2AddrDec,
    input [`REG_FILE_MSB:0] i_RfReadDstExec,
    input i_BranchVerification,
    input i_BranchBit,
    input i_JmpBit,
    input i_RetiBit,
    input i_RdMemExe,   //devia estar RdEnMemExe
    input i_WeMemEnable,
    input i_AluEnDec,
    input i_InterruptSignal,
    

    output reg o_FlushFetch,
    output reg o_FlushDecode,
    output reg o_FlushExecute,
    output reg o_FlushMemory,
    output o_StallSignal
);





always @(posedge i_Clk) begin
//    if (i_Clk) begin
        if(i_Rst == 1'b1) begin
            o_FlushDecode <= 0;
            o_FlushExecute <= 0;
            o_FlushFetch <= 0;
            o_FlushMemory <= 0;
        end
        else begin  
            if(i_InterruptSignal == 1'b1) begin
                o_FlushDecode <= 1;
                o_FlushExecute <= 1;
                o_FlushFetch <= 1;
                //o_FlushMemory <= 1;
            end
            //necessário esta ordem pois quando houver uma interrupçao e estiver a ser executado um JMP,
            //o JMP não vai ser executado e e em vez disso, o endereço de salto vai passar a ser o 
            //endereço de retorno da interrupção.
            //Assim, quando acontecer o RETI, está a executar o JMP que não foi executado previamente
            else if((i_BranchVerification == 1'b1 && i_BranchBit == 1'b1)) begin
                o_FlushDecode <= 1;
                o_FlushExecute <= 1;
                o_FlushFetch <= 1;
                o_FlushMemory <= 1;
            end
            else if(i_JmpBit == 1'b1) begin
                o_FlushDecode <= 1;
                o_FlushExecute <= 1;
                o_FlushFetch <= 1;
                //o_FlushMemory <= 1;
            end 
            else if(i_RetiBit == 1'b1) begin
                o_FlushDecode <= 1;
                o_FlushExecute <= 1;
                o_FlushFetch <= 1;
                o_FlushMemory <= 1;
            end 
            else begin
                o_FlushDecode <= 0;
                o_FlushExecute <= 0;
                o_FlushFetch <= 0;
                o_FlushMemory <= 0;
            end
        end  
    end 
/*    else begin
        if (i_Rst) begin
            //Do nothing
        end
        else begin
            o_FlushDecode <= 0;
            o_FlushExecute <= 0;
            o_FlushMemory <= 0;
        end 
    end 
end*/

//Stall signal = 1 -> LD in Decode to same Rdst of EX stage 
assign o_StallSignal = ((i_RdMemExe && i_AluEnDec) && (i_RfReadDstExec == i_IrRead1AddrDec)) ? 1'b1 : 
                       ((i_RdMemExe && i_AluEnDec) && (i_RfReadDstExec == i_IrRead2AddrDec)) ? 1'b1 : 
                       ((i_RdMemExe && i_WeMemEnable) && (i_RfReadDstExec == i_IrRead2AddrDec)) ? 1'b1 : 1'b0;

                        
endmodule
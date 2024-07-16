`timescale 1ns / 1ps

`include "Constants.v"

/// \input i_Clk Source Clock signal for the slave device, logic is processed on rising edges of this signal
/// \input i_Rst Reset signal for the module, active high
/// \input i_Stall Stall signal, stops PC from changing when high
/// \input i_PcSel Mux selection pins for the next Program Counter (PC) values
/// \input i_PcJmp Value PC is updated to when i_PcSel == PC_SEL_JMP
/// \input i_PcBxx Value PC is updated to when i_PcSel == PC_SEL_BXX
/// \input i_PcRet Value PC is updated to when i_PcSel == PC_SEL_RET
/// \input i_PcInt Value PC is updated to when i_PcSel == PC_SEL_INT
/// \output o_Rdy This signal is pulled high when the module is ready for execution
/// \output o_InstructionRegister Current output from the code memory
/// \output o_ProgramCounter Current PC value

module InstructionFetch
(
    input i_Clk,
    input i_Rst,
    input i_Stall,
    input i_Flush,
    input i_Enable,
    input [`PC_SEL_MSB:0] i_PcSel,
    input [`BUS_MSB:0] i_PcJmp,
    input [`BUS_MSB:0] i_PcBxx,
    input [`BUS_MSB:0] i_PcRet,
    input [`BUS_MSB:0] i_PcInt,
    input [`BUS_MSB:0] i_PcReti,
    
    output o_Rdy,
    output [`BUS_MSB:0] o_InstructionRegister,
    output reg [`BUS_MSB:0] o_ProgramCounter
);

/*
ila_0 _ila (
	.clk(i_Clk), // input wire clk


	.probe0(i_Rst), // input wire [0:0]  probe0  
	.probe1(w_CodeMemBusy), // input wire [0:0]  probe1 
	.probe2(i_Enable), // input wire [0:0]  probe2 
	.probe3(r_PcReady) // input wire [0:0]  probe3
);
*/


wire w_CodeMemBusy;
wire [`BUS_MSB:0] w_CodeMemOut;
reg r_PcReady;
wire [`BUS_MSB:0] w_ProgramCounter;

assign o_Rdy = w_CodeMemBusy;
//assign o_InstructionRegister = w_CodeMemOut;
assign o_InstructionRegister = i_Flush ? 0 : ((i_Enable == 1'b1 && r_PcReady == 1'b1) ? w_CodeMemOut : 32'd0);       //possibilidade de criar enable para pc e para ir devido ao facto da primeira instrução acontecer em 2 ciclos

assign w_ProgramCounter = (i_Stall) ? o_ProgramCounter - 4 : o_ProgramCounter;   // addr da memória fica durante 2 ciclos o PC e depois PC - 4 para manter o valor de modo a não se perder a instrução

CodeMemory _CodeMem
(
    .clka(i_Clk),            
    .rsta(i_Rst),
    .ena(!i_Rst),            
    .wea(0),              
    .addra(w_ProgramCounter),         
    .dina(0),           
    .douta(w_CodeMemOut),         
    .rsta_busy(w_CodeMemBusy)
);
    
always @(posedge i_Clk) begin
    if (i_Rst) begin
        o_ProgramCounter <= 0;
        r_PcReady <= 0;
    end
    else begin
        if (i_Enable) begin
        r_PcReady <= 1;
            if (i_Stall) begin
                o_ProgramCounter <= o_ProgramCounter;
            end
            else begin
                    case (i_PcSel)
                    `PC_SEL_BXX: begin
                        o_ProgramCounter <= i_PcBxx;
                    end

                    `PC_SEL_JMP: begin
                        o_ProgramCounter <= i_PcJmp;
                    end

                    `PC_SEL_RET: begin
                        o_ProgramCounter <= i_PcRet;
                    end 

                    `PC_SEL_RETI: begin
                        o_ProgramCounter <= i_PcReti;
                    end 

                    `PC_SEL_INT: begin
                        o_ProgramCounter <= i_PcInt;
                    end
                    
                    default: o_ProgramCounter <= o_ProgramCounter + `PC_INC;
                endcase
                
            end
        end
        else begin
            //Do nothing
        end
    end
end

endmodule

`timescale 1ns / 1ps


module InstructionExecute
(
    input i_Clk,
    input i_Rst,

    input [`BUS_MSB:0] i_ProgramCounter,

    //alu signals
    input [`ALU_SEL_MSB:0] i_AluCtrl,
    input i_AluEn,
    input i_AluOp2Sel,
    input i_UpdateCondCodes,

    //hazard multiplexers
    input [1:0] i_ForwardOp1,
    input [1:0] i_ForwardOp2,

    input [`BUS_MSB:0] i_AluOutMem,     //register value from MEM stage
    input [`BUS_MSB:0] i_RfOutValue,    //register value from EXE stage
    input [`BUS_MSB:0] i_Immed22Mem,    //value from MEM stage to LDI

    input [`BUS_MSB:0] i_R1Out,         //RF_Read1
    input [`BUS_MSB:0] i_R2Out,         //RF_Read2
    input [`BUS_MSB:0] i_Imm16,
    input [`BUS_MSB:0] i_Imm17,
    input [`BUS_MSB:0] i_Imm22,
    input [`BUS_MSB:0] i_Imm23,
    
    input i_BranchVerification,
    input [`PC_SEL_MSB:0] i_PcSel,
    input i_BranchBit,

    //outputs
    output [`PC_SEL_MSB:0] o_PcSelExe2Fetch,
    

    //outputs
    output [`BUS_MSB:0] o_PcJmp,
    output [`BUS_MSB:0] o_PcBranch,
    
    output [`BUS_MSB:0] o_AluOut,
    output [`BUS_MSB:0] o_AluOp2,
    
    output [`BUS_MSB:0] o_Imm22,
    output [`BUS_MSB:0] o_ImmOpX,

    //flags
    output [3:0] o_AluConditionCodes    //ConditionCodes <= {Carry, Zero, Negative, Overflow};
);

wire [`BUS_MSB:0] w_AluOp1;
wire [`BUS_MSB:0] w_AluIn2;             //ALU second source

//verified the PC select if is a branch if this is or not taken
assign o_PcSelExe2Fetch = (i_BranchVerification == 1'b0 && i_BranchBit == 1'b1) ? `PC_SEL_ADD4 : i_PcSel;

assign o_PcJmp = i_Imm16 + w_AluOp1;

assign o_PcBranch = i_ProgramCounter + i_Imm23;

assign o_ImmOpX = w_AluOp1 + i_Imm17;

assign w_AluOp1 = (i_ForwardOp1 == 2'b00) ? i_R1Out :
                  (i_ForwardOp1 == 2'b01) ? i_AluOutMem :
                  (i_ForwardOp1 == 2'b11) ? i_Immed22Mem : i_RfOutValue;

assign o_AluOp2 = (i_ForwardOp2 == 2'b00) ? i_R2Out :
                  (i_ForwardOp2 == 2'b01) ? i_AluOutMem : 
                  (i_ForwardOp2 == 2'b11) ? i_Immed22Mem : i_RfOutValue;  //Rf_wb

assign w_AluIn2 = (i_AluOp2Sel == 1'b0) ? o_AluOp2 : i_Imm16;


ALU alu
(
    .i_Clk(i_Clk),
    .i_Rst(i_Rst),
    .i_Enable(i_AluEn),
    .i_UpdateCondCodes(i_UpdateCondCodes),
    .i_OpCtrl(i_AluCtrl),
    .i_LeftOp(w_AluOp1),
    .i_RigthOp(w_AluIn2),
    .o_Output(o_AluOut),
    .o_ConditionCodes(o_AluConditionCodes)
);

endmodule

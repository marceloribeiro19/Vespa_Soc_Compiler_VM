`timescale 1ns / 1ps

`include "Constants.v"

module ControlUnit
(
    input i_Clk,
    input i_Rst,
    
    //Incoming signals from Decode
    input [`OPCODE_MSB:0] i_OpCode,
    input i_ImmOp,

    //Peripheral ready signals
    input i_FetchRdy,
    input i_DataMemRdy, 
    
    //ALU Control
    output [`ALU_SEL_MSB:0] o_AluCtrl,
    output o_AluEn,
    output o_AluOp2Sel,
    output o_UpdateCondCodes,
    
    //Data Bus Signals 
    output o_WrEnMem,
    output o_RdEnMem,

    output o_WrEnRf,
    
    //datapath multiplexers selectors   
    output [`PC_SEL_MSB:0] o_PcSel,
    output o_MemAddrSel,
    output [`RF_SEL_MSB:0] o_RfRdAddrBSel,    //Register File Read Address for port B
    output [`RF_IN_SEL_MSB:0] o_RfDataInSel,  //Register File input data selection  
    
    output o_JmpBit,
    output o_BranchBit,
    output o_RetiBit,
    output o_Enable,

    input i_IntRequest,
    input [1:0] i_IntNumber,
    input i_IntPending,
    output o_IntAckComplete,
    output o_IntAckAttended, 
    output [`BUS_MSB:0] o_IntAddress,
    
    
    //branch signals
    input [3:0] i_BranchCond,
    input i_BranchBitExe,
    input [3:0] i_AluConditionCodes, 
    output o_BranchVerification
    
);

integer i;

parameter ST_INIT   = 2'b00;
parameter ST_RUN    = 2'b01;
parameter ST_HALT   = 2'b10;
parameter ST_INT    = 2'b11;

(* keep *) wire w_PeripheralsRdy;
reg [8:0] counter;

//usado em simulação timing post-synthesis
assign w_PeripheralsRdy = (counter == 'd20);   

always @(posedge i_Clk) begin
    if(i_Rst) begin
        counter <= 0;
    end
    else if(counter != 20) begin
        counter <= counter + 1;
    end 
    else begin
        counter <= counter;
    end
end



reg [2:0] r_CurrentState;

always @(posedge i_Clk) begin
    if (i_Rst) begin
        r_CurrentState <= ST_INIT;
    end
    else begin
        case (r_CurrentState)
            ST_INIT: begin
                if (w_PeripheralsRdy == 1'b1) begin
                    r_CurrentState <= ST_RUN;    
                end
                else begin
                    r_CurrentState <= ST_INIT;
                end
            end

            ST_RUN: begin
                if(i_IntRequest) begin
                    r_CurrentState <= ST_INT;
                end
                else begin
                    r_CurrentState <= ST_RUN;           
                end
            end
            
            ST_INT: begin
                //TODO: Missing handling INT ack
                r_CurrentState <= ST_RUN;
            end
            
            ST_HALT: begin
               r_CurrentState <= ST_HALT;
            end

            default: 
                r_CurrentState <= ST_HALT;
        endcase
    end
end

assign o_PcSel = (r_CurrentState == ST_RUN) ? ((i_IntRequest == 1'b1)? `PC_SEL_INT :
                                               (i_OpCode == `OP_BXX) ? `PC_SEL_BXX :
                                               (i_OpCode == `OP_JMP) ? `PC_SEL_JMP :
                                               (i_OpCode == `OP_RET) ? `PC_SEL_RET :
                                               (i_OpCode == `OP_RETI && !i_IntPending) ? `PC_SEL_RETI: 
                                               (i_OpCode == `OP_RETI &&  i_IntPending) ? `PC_SEL_INT : `PC_SEL_ADD4) : 
                                               (r_CurrentState == ST_INIT)? `PC_SEL_ADD4 : 0;

assign o_RfRdAddrBSel = (i_OpCode == `OP_ST || i_OpCode == `OP_STX) ? `RF_SEL_RST : 
                        (i_OpCode == `OP_RET) ? `RF_SEL_RET :
                        (i_OpCode == `OP_RETI) ? `RF_SEL_RETI : `RF_SEL_RS2;

assign o_RfDataInSel = (i_OpCode == `OP_JMP && i_ImmOp == 1'b1) ? `RF_IN_PC :
                       (i_OpCode == `OP_LD || i_OpCode == `OP_LDX) ? `RF_IN_MEM_OUT:
                       (i_OpCode == `OP_LDI) ? `RF_IN_IMM : `RF_IN_ALU;

assign o_WrEnRf = (i_OpCode == `OP_ADD || i_OpCode == `OP_SUB || i_OpCode == `OP_OR  ||
                   i_OpCode == `OP_AND || i_OpCode == `OP_NOT || i_OpCode == `OP_XOR ||
                   i_OpCode == `OP_LDI || i_OpCode == `OP_LDX || i_OpCode == `OP_LD  ||
                  (i_OpCode == `OP_JMP && i_ImmOp == 1'b1)) ? 1'b1 : 1'b0;

assign o_WrEnMem = (i_OpCode == `OP_ST || i_OpCode == `OP_STX) ? 1'b1 : 1'b0;

assign o_RdEnMem = (i_OpCode == `OP_LD || i_OpCode == `OP_LDX) ? 1'b1 : 1'b0;

assign o_MemAddrSel = (i_OpCode == `OP_LDX || i_OpCode == `OP_LDX) ? `MEM_SEL_OPX : `MEM_SEL_IMM ;

assign o_AluCtrl =  (i_OpCode == `OP_ADD) ? 3'b001 :
                    (i_OpCode == `OP_SUB || i_OpCode == `OP_CMP) ? 3'b010 :
                    (i_OpCode == `OP_OR)  ? 3'b011 : 
                    (i_OpCode == `OP_AND) ? 3'b100 :
                    (i_OpCode == `OP_NOT) ? 3'b101 : 
                    (i_OpCode == `OP_XOR) ? 3'b110 : 3'b000;

assign o_AluOp2Sel = (i_ImmOp == 1'b1) ? 1'b1 : 1'b0;

assign o_AluEn = (i_OpCode == `OP_ADD || i_OpCode == `OP_SUB || i_OpCode == `OP_OR  ||
                  i_OpCode == `OP_AND || i_OpCode == `OP_NOT || i_OpCode == `OP_XOR ||
                  i_OpCode == `OP_CMP) ? 1'b1 : 1'b0;

assign o_JmpBit = (i_OpCode == `OP_JMP) ? 1'b1 : 1'b0;

assign o_BranchBit = (i_OpCode == `OP_BXX) ? 1'b1 : 1'b0;

assign o_RetiBit = (i_OpCode == `OP_RETI) ? 1'b1 : 1'b0;

assign o_Enable = (r_CurrentState == ST_RUN) || (r_CurrentState == ST_INT) ? 1'b1 : 1'b0;

assign o_UpdateCondCodes = (i_OpCode == `OP_ADD || i_OpCode == `OP_SUB || i_OpCode == `OP_CMP) ? 1'b1 : 1'b0;

assign o_IntAckAttended = (r_CurrentState == ST_INT) ? 1'b1 : 1'b0;

assign o_IntAckComplete = (i_OpCode == `OP_RETI) ? 1'b1 : 1'b0;

assign o_IntAddress = (i_IntNumber == 2'd0) ? `ISR1_ADDRESS :
                      (i_IntNumber == 2'd1) ? `ISR2_ADDRESS :
                      (i_IntNumber == 2'd2) ? `ISR3_ADDRESS : `ISR4_ADDRESS;

check_branchcond branch_module
(
    .i_BranchCond(i_BranchCond),
    .i_BranchBitExe(i_BranchBitExe),
    .i_AluConditionCodes(i_AluConditionCodes),    // {w_Carry, w_Zero, w_Negative, w_Overflow}
    
    .o_BranchVerification(o_BranchVerification)
);

endmodule

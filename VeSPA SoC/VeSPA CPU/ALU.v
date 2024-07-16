`timescale 1ns / 1ps

`include "Constants.v"

module ALU
(
    input i_Clk,
    input i_Rst,
    input i_Enable,
    input i_UpdateCondCodes,
    input [`ALU_SEL_MSB:0] i_OpCtrl,
    input [`BUS_MSB:0] i_LeftOp,
    input [`BUS_MSB:0] i_RigthOp,
    output [`BUS_MSB:0] o_Output,
    output reg [`CCODES_MSB:0] o_ConditionCodes
);

wire w_Carry, w_Zero, w_Negative, w_Overflow, w_Sub;
wire [(`BUS_MSB + 1):0] w_Output;

assign w_Sub = (i_OpCtrl == `OP_SUB);

assign w_Overflow = (o_Output[`BUS_MSB] & ~i_LeftOp[`BUS_MSB] & ~(w_Sub ^ i_RigthOp[`BUS_MSB]))  |
                    (~o_Output[`BUS_MSB] & ~i_LeftOp[`BUS_MSB] & (w_Sub ^ i_LeftOp[`BUS_MSB]));

assign w_Carry = w_Output[(`BUS_MSB + 1)];
assign w_Negative = o_Output[`BUS_MSB];
assign w_Zero = ~(|o_Output);

assign o_Output = w_Output[`BUS_MSB:0];

assign w_Output = (i_OpCtrl == `OP_ADD) ? (i_LeftOp + i_RigthOp) :
                  (i_OpCtrl == `OP_SUB) ? (i_LeftOp - i_RigthOp) :
                  (i_OpCtrl == `OP_AND) ? (i_LeftOp & i_RigthOp) :
                  (i_OpCtrl == `OP_OR) ? (i_LeftOp | i_RigthOp) :
                  (i_OpCtrl == `OP_XOR) ? (i_LeftOp ^ i_RigthOp) :
                  (i_OpCtrl == `OP_NOT) ? (~i_LeftOp) : 0;
                  
always @(posedge i_Clk) begin
    if (i_Rst) begin
        o_ConditionCodes <= 0;
    end
    else begin
        if (i_Enable) begin
            if (i_UpdateCondCodes) begin
                o_ConditionCodes <= {w_Carry, w_Zero, w_Negative, w_Overflow};
            end
            else begin
                o_ConditionCodes <= o_ConditionCodes;
            end
        end 
        else begin
            //Do nothing
        end
    end 
end

endmodule

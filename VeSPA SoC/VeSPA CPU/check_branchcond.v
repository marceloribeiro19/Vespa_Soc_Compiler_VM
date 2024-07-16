`timescale 1ns / 1ps

//check branch condition module
module check_branchcond(

    input [3:0] i_BranchCond,
    input i_BranchBitExe,
    input [3:0] i_AluConditionCodes,// {w_Carry, w_Zero, w_Negative, w_Overflow}  [3, 2, 1, 0]
    
    output reg o_BranchVerification
    );
    
    wire c, z, n, v;
    
    assign c = i_AluConditionCodes[3];
    assign z = i_AluConditionCodes[2];
    assign n = i_AluConditionCodes[1];
    assign v = i_AluConditionCodes[0];
    
    
    //BRANCH CONDITIONS PARAMETERS
    parameter BRA = 4'd0,
              BCC = 4'd1,
              BVC = 4'd2,
              BEQ = 4'd3,
              BGE = 4'd4,
              BGT = 4'd5,
              BPL = 4'd6,
              BNV = 4'd8,
              BCS = 4'd9,
              BVS = 4'd10,              
              BNE = 4'd11, 
              BLT = 4'd12,
              BLE = 4'd13,
              BMI = 4'd14;
             
    
     always @(*) begin    
        case (i_BranchCond)
            BRA:   //branch always 
                o_BranchVerification <= 1;
             
            BNV:   //branch never
                o_BranchVerification <= 0;
             
            BCC:   //branch if not carry 
                o_BranchVerification <= ~c;
             
            BCS:   //branch if carry
                o_BranchVerification <= c;
             
            BVC:   //branch if not overflow
                o_BranchVerification <= ~v;
             
            BVS:   //branch if overflow
                o_BranchVerification <= v;
             
            BEQ:   //branch if equal 
                o_BranchVerification <= z; 
            
            BNE:   //branch if not equal
                o_BranchVerification <= ~z;
            
            BGE:   //branch if greater than or equal
                o_BranchVerification <= (~n & ~v) | (n & v);
                
            BLT:   //branch if less than
                o_BranchVerification <= (n & ~v) | (~n & v);       
            
            BGT:   //branch if greater than 
                o_BranchVerification <= ~z & ((~n & ~v) | (n & v));
            
            BLE:   //branch if less than or equal
                o_BranchVerification <= z | ((n & ~v) | (~n & v));
            
            BPL:   //branch if plus 
                o_BranchVerification <= ~n;
            
            BMI:   //branch if minus
                o_BranchVerification <= n;
                
            default: o_BranchVerification <= 0;
         endcase
     end     
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/26/2024 11:31:39 AM
// Design Name: 
// Module Name: interruptController_wrapper
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



module interruptController_wrapper(
    input i_Clk, 
    input i_Rst, 
    input i_WEnable,
    input [31:0] i_WAddr,
    input [31:0] i_WData,
    input i_REnable,
    input [31:0] i_RAddr,
    output reg [31:0] o_RData,
    output reg o_Err, 
    
    input int_source0,
    input int_source1,
    input int_source2,
    input int_source3,
    input ack_complete,
    input ack_attended, 
    output int_pending,
    output int_attending,
    output irq_req,
    output [1:0]irq_number
);
    

interruptController inst1(
    .rst(i_Rst),
    .clk(i_Clk),
    .int_sources({int_source3, int_source2, int_source1, int_source0}),
    .int_ack_complete(ack_complete),
    .int_ack_attended(ack_attended),
    .int_pending(int_pending),
    .int_attending(int_attending),
    .int_req(irq_req),
    .int_number(irq_number),
    .ea(r_ea),
    .en1(r_en1),
    .en2(r_en2),
    .en3(r_en3)
);

reg r_ea, r_en1, r_en2, r_en3;

always @(posedge i_Clk) begin
    if (i_Rst) begin
        r_ea  <= 0;
        r_en1 <= 0;
        r_en2 <= 0;
        r_en3 <= 0;
    end
    else begin
        if (i_WEnable)  begin
            //Verify it the write address is within range
            case (i_WAddr)
                2'b00: begin
                    {r_en3, r_en2, r_en1, r_ea} = i_WData[3:0];
                    o_Err <= 0;
                end

                default: o_Err <= 1;
            endcase
        end
        //Check if there is a read request pending
        else if (i_REnable) begin
             case (i_RAddr)
                2'b00: begin
                    o_RData <= {27'b0, r_en3, r_en2, r_en1, r_ea};
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
    
    
endmodule

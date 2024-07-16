`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/05/2024 10:44:27 PM
// Design Name: 
// Module Name: interruptController
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

module interruptController(
    input rst,
    input clk,
    input [3:0] int_sources,
    input int_ack_complete,
    input int_ack_attended,
    output reg int_req,
    output reg [1:0]int_number,
    output reg int_pending,
    input ea,
    input en1,
    input en2,
    input en3
);


wire [3:0] int_sources_2;
wire [2:0]nextIrq; 
reg [2:0]currIrq; 
reg [3:0]pending;
reg [3:0]int_sources_prev;

//sources activation
assign int_sources_2[0] = int_sources[0] && ea;
assign int_sources_2[1] = int_sources[1] && en1 && ea;
assign int_sources_2[2] = int_sources[2] && en2 && ea;
assign int_sources_2[3] = int_sources[3] && en3 && ea;


//checks the next interrupt to be attended according to priorities
assign nextIrq = (pending[3] && ~pending[2] && ~pending[1] && ~pending[0]) ? 3'b011 :
                 (pending[2] && ~pending[1] && ~pending[0]) ? 3'b010 :
                 (pending[1] && ~pending[0]) ? 3'b001 : 
                 (pending[0]) ? 3'b000 : 3'b100;


//asynchronous source checking
always@(*) begin 
    if(rst == 1'b1) begin
        pending <= 4'b0000;
        int_sources_prev <= 4'b0000;
    end
    else begin
        if(int_sources_2 != int_sources_prev) begin      //if any of the sources changed state
            pending <= pending | int_sources_2;          //when the source reaches zero it does not change          
            int_sources_prev <= int_sources_2;           //so changes only on rising edge
        end 
        else begin
            if(int_ack_complete) begin
                pending <= pending & ~(4'b0001 << currIrq);
            end
            else begin
                //Do nothing
            end
        end
    end
end


always @(posedge clk) begin
 
    if(rst == 1'b1) begin
        int_req <= 1'b0;
        int_number <= 2'b0;
        currIrq <= 3'b100;
        int_pending <= 1'b0;
    end
    else begin
        if(int_ack_complete) begin          //when receive an ack, update completed variable         
            if(!nextIrq[2]) begin
                //int_pending <= 1'b1;
                int_req <= 1'b1;
                int_number <= nextIrq[1:0];
            end
            else begin
                //int_pending <= 1'b0;
                currIrq <= 3'b100;
            end
        end
        else if(int_ack_attended) begin
            int_req <= 1'b0;
            currIrq <= nextIrq;
            int_pending <= ((pending & ~(4'b0001 << nextIrq)) != 0);
        end
        else if(currIrq[2] && !nextIrq[2]) begin
            int_req <= 1'b1;
            int_number <= nextIrq[1:0];
        end
        else begin
            //Do nothing
        end
    end
end


//assign int_pending = !nextIrq[2];



endmodule
`timescale 1ns / 1ps

module UartBaudRate
(
    input rst,
    input clk,
    input enable,
    input [31:0] baudrate_counter,
    output reg tick
);
    wire clk2;
    assign clk2 = clk & enable; //if disabled, stop the internal clock
    reg [31:0] internal_counter;

    always @(posedge clk2) begin
        if(rst) begin
            tick <= 0;
            internal_counter <= 1;
        end
        else if (internal_counter == 1) begin
            tick <= ~tick;                                      //toggle tick bit
            internal_counter <= {1'b0, baudrate_counter[31:1]}; //divide the counter by 2 and update internal counter
        end
        else begin
            internal_counter <= internal_counter - 1; //decrement counter
        end
    end
endmodule
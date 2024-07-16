`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/18/2024 04:23:54 PM
// Design Name: 
// Module Name: ps2_new
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
module ps2_new(
    input clk,
    input reset,
    input PS2_enable,
    input PS2C,                     // clock signal from PS2 peripheral
    input PS2D,                     // bit read from PS2 peripheral
    output o_error,                 // error flag
    output [7:0] o_key,             // read key
    output [3:0] o_Data
);
    
parameter S_CLEAN = 2'b00;
parameter S_IDLE = 2'b01;
parameter S_RECEIVE = 2'b10;
parameter S_CHECK_ERROR = 2'b11;

reg [1:0] state;                // FSM state
reg [10:0] data_read;           // all 11 bits read from PS2 peripheral
reg [3:0] counter;              // counter of read bits
reg parity;                     // parity register
reg previous_PS2C;              // previous PS2 clock to detect transition
reg [11:0] ticks;               // ticks to reduce sampling frequency
reg [7:0] key;                  // key pressed
reg error;                      // error register

assign o_key = key;
assign o_error = error;

always @(posedge clk) begin
    if (reset) begin
        state <= S_IDLE;
        data_read <= 11'b0;
        counter <= 4'b0;
        error <= 1'b0;
        key <= 8'b0;
        previous_PS2C <= 1'b1;
        parity <= 1'b1;
        ticks <= 12'b0;
    end
    else begin
        ticks <= ticks + 1'b1;
        if(PS2_enable == 1'b1 && ticks >= 12'd4000) begin
            ticks <= 1'b0;
            case (state)
                S_CLEAN: begin
                    data_read <= 11'b0;
                    counter <= 4'b0;
                    previous_PS2C <= 1'b1;
                    parity <= 1'b1;
                    state <= S_IDLE;
                    ticks <= 12'd4000;
                end
                
                S_IDLE: begin
                     if ((~PS2C) && previous_PS2C) begin                           
                        error <= 1'b0;
                        state <= S_RECEIVE;
                        ticks <= 12'd4000;
                    end
                end
                
                S_RECEIVE: begin
                    if ((~PS2C) && previous_PS2C) begin         // falling edge on PS2C -> PS2D can be read
                        data_read <= {data_read[9:0], PS2D};    // concatenate PS2D in the LSB of data_read
                        counter <= counter + 4'b1;
                    end
                    if (counter > 4'd1 && counter < 4'd10) begin
                        parity <= parity ^ PS2D;
                    end
                    else if (counter == 4'd11) begin        // all 11 bits were read
                        state <= S_CHECK_ERROR;
                    end
                    previous_PS2C <= PS2C;
                end
                
                S_CHECK_ERROR: begin
                    if ((data_read[10] != 1'b0) || (data_read[0] != 1'b1)) begin        // verify start and stop
                        error <= 1'b1;
                    end
                
                    else if (parity != data_read[1]) begin      // verify parity
                        error <= 1'b1;
                    end
                    else begin
                        key <= {data_read[2], data_read[3], data_read[4], data_read[5], data_read[6], data_read[7], data_read[8], data_read[9]};
                    end
                    state <= S_CLEAN;
                end
                
                default: begin
                    state <= S_IDLE;
                end  
            endcase
        end
    end
end
endmodule
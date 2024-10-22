`timescale 1ns / 1ps

/// \brief Template interface for VeSPA Custom Bus slave device
/// \input i_Clk Source Clock signal for the slave device, logic is processed on rising edges of this signal
/// \input i_Rst Reset signal for the device, active high
/// \input i_WEnable Write Enable signal. If this signal is set to high during a rising edge of the clock,
/// data is writen to the slave register file
/// \input i_WAddr Address of the register file that data should be writen to. This is a virtual address,
/// that should be generated by a Bus Interconnect device
/// \input i_WData Data writen to the slave register file if all the required conditions are complied
/// \input i_REnable Read Enable signal. If this signal is set to high during a rising edge of the clock,
/// data is read from the slave register file
/// \input i_RAddr Address of the register file that data will be read from. Simmilar to the i_WAddr, this
/// address should be generated by a Bus Interconnect device
/// \output o_RData When a read operation occurs, data is put on this output
/// \output o_Err This signal indicated an internal error occured on the device, such as an invalid address
module Uart
(
    //Bus related signals
    input i_Clk,
    input i_Rst,
    input i_WEnable,
    input [31:0] i_WAddr,
    input [31:0] i_WData,
    input i_REnable,
    input [31:0] i_RAddr,
    output reg [31:0] o_RData,
    output reg o_Err,
    //User signals begin here
    input i_Rx,
    output o_Tx
);

wire w_UartTick, w_TxDone, w_RxDone;
wire [7:0] w_DataOut;

reg r_Enable, r_TxStart, r_RxEnable;
reg [7:0] r_DataIn;
reg [31:0] r_BaudRate;
reg prev_TxDone;

reg [31:0] r_RAddr;
reg r_REnable;

UartBaudRate _UartBaudRate
(
    .rst(i_Rst),
    .clk(i_Clk),
    .enable(r_Enable),
    .baudrate_counter(r_BaudRate),
    .tick(w_UartTick)
);

UartTx _UartTx
(
    .tick(w_UartTick),
    .tx_start(r_TxStart),
    .data_in(r_DataIn),
    .rst(i_Rst),
    .tx_bit(o_Tx),
    .tx_done(w_TxDone)
);

UartRx _UartRx
(
    .tick(w_UartTick),
    .rst(i_Rst),
    .rx_en(r_RxEnable),
    .rx_bit(i_Rx),
    .data_out(w_DataOut),
    .rx_done(w_RxDone)
);


always @(posedge i_Clk) begin
    if (i_Rst) begin
        r_Enable    <= 0;
        r_TxStart   <= 0;
        r_RxEnable  <= 0;
        r_DataIn    <= 0;
        o_Err       <= 0;
        r_BaudRate  <= 0;
        prev_TxDone <= 0;
    end
    else begin
        //Check if there is a write request pending
        if ((w_TxDone == 1'b1) && (prev_TxDone == 1'b0)) begin
            r_TxStart = 0;
            prev_TxDone <= w_TxDone;
        end    
        else begin
            prev_TxDone <= w_TxDone;
        end
        

        if (i_WEnable) begin
            //Verify it the write address is within range
            case (i_WAddr)
                2'b00: begin
                    {r_TxStart, r_RxEnable, r_Enable} = i_WData[2:0];
                    o_Err <= 0;
                end

                2'b01: begin
                    r_BaudRate <= i_WData;
                    o_Err <= 0;
                end

                2'b10: begin
                    r_DataIn <= {24'b0, i_WData[7:0]};
                    o_Err <= 0;
                end
                default: o_Err <= 1;
            endcase
        end
        //Check if there is a read request pending
        else if (i_REnable) begin
             case (i_RAddr)
                2'b00: begin
                    o_RData <= {27'b0, w_RxDone, w_TxDone, r_TxStart, r_RxEnable,r_Enable};
                    o_Err <= 0;
                end

                2'b01: begin
                    o_RData <= r_BaudRate;
                    o_Err <= 0;
                end

                2'b10: begin
                    o_RData <= r_DataIn;
                    o_Err <= 0;
                end

                2'b11: begin
                    o_RData <= w_DataOut;
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


always @(posedge i_Clk) begin
    if(i_Rst) begin
        r_RAddr <= 0;
        r_REnable <= 0;
    end
    else begin
        r_RAddr <= i_RAddr;
        r_REnable <= i_REnable;
    end 
end

endmodule

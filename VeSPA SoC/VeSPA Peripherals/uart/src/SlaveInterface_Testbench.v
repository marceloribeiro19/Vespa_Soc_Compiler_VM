`timescale 1ns / 1ps

module SlaveInterfaceTestbench();

reg r_Clk, r_Rst, r_WEnable, r_REnable, r_Rx, r_Done;
reg [31:0] r_WAddr, r_RAddr, r_WData;
wire w_Err, w_MemBusy, w_Tx;
wire [31:0] w_RData;

Uart _Dut
(
    .i_Clk(r_Clk),
    .i_Rst(r_Rst),
    .i_WEnable(r_WEnable),
    .i_WAddr(r_WAddr),
    .i_WData(r_WData),
    .i_REnable(r_REnable),
    .i_RAddr(r_RAddr),
    .o_RData(w_RData),
    .o_Err(w_Err),
    .i_Rx(r_Rx),
    .o_Tx(w_Tx)
);

always #1 r_Clk <= r_Clk ^ 1;

initial begin
    r_Done <= 0;
    r_Rst <= 1;
    r_Clk <= 0;
    r_WAddr <= 0;
    r_WEnable <= 0;
    r_REnable <= 0;
    r_RAddr <= 0;
    r_WData <= 0;
    #2;
    r_Rst <= 0;
    
    #2;
    r_WEnable <= 1;
    r_WAddr <= 1;
    r_WData <= 13021;
    #2;
    r_WEnable <= 0;
    
    #2;
    r_WAddr <= 2;
    r_WData <= 8'h55;
    r_WEnable <= 1;
    #2;
    r_WEnable <= 0;
    
    
    #2;
    r_WAddr <= 0;
    r_WData <= 8'b00000101;
    r_WEnable <= 1;
    #2;
    r_WEnable <= 0;
    
    
    #290000;
    r_WEnable <= 1;
    r_WAddr <= 2;
    r_WData <= 8'hAA;
    #2;
    r_WEnable <= 0;
    
    
    #2;
    r_WAddr <= 0;
    r_WData <= 8'b00000101;
    r_WEnable <= 1;
    #2;
    r_WEnable <= 0;
    
    #10;
end

endmodule

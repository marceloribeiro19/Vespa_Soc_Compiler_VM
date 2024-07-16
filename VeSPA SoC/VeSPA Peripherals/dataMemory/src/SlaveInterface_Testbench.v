`timescale 1ns / 1ps

module SlaveInterfaceTestbench();

reg r_Clk, r_Rst, r_WEnable, r_REnable;
reg [31:0] r_WAddr, r_RAddr, r_WData;
wire w_Err, w_MemBusy;
wire [31:0] w_RData;

SlaveInterface _Dut
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
    .o_MemBusy(w_MemBusy)
);

always #1 r_Clk <= r_Clk ^ 1;

initial begin
    r_Rst <= 1;
    r_Clk <= 0;
    r_WAddr <= 0;
    r_WEnable <= 0;
    r_REnable <= 0;
    r_RAddr <= 0;
    r_WData <= 0;
    #2;
    r_Rst <= 0;
    while (w_MemBusy) begin
        #1;
    end
    #2;
    r_WEnable <= 1;
    r_WData <= 32'hAA55AA55;
    r_WAddr <= 0;
    #2;
    r_WEnable <= 0;
    r_RAddr <= 0;
    r_REnable <= 1;
    #10;
    $finish;
end

endmodule

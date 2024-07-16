`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2024 11:33:10 PM
// Design Name: 
// Module Name: custom_interconnect_tb
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


module custom_interconnect_tb( );

reg r_WEnable, r_REnable;
reg [31:0] r_WAddr, r_WData, r_RAddr, r_RData_0, r_RData_2;

wire [31:0] out_RData, out_WAddr_0, out_WData_0, out_RAddr_0, out_WAddr_2, out_WData_2, out_RAddr_2;
wire out_WEnable_0, out_REnable_0, out_WEnable_2, out_REnable_2;


CustomInterconnect test(
    .i_WEnable(r_WEnable), 
    .i_WAddr(r_WAddr),
    .i_WData(r_WData),
    .i_REnable(r_REnable), 
    .i_RAddr(r_RAddr),
    .o_RData(out_RData), 

    .o_WEnable_0(out_WEnable_0), 
    .o_WAddr_0(out_WAddr_0),
    .o_WData_0(out_WData_0),
    .o_REnable_0(out_REnable_0), 
    .o_RAddr_0(out_RAddr_0),
    .i_RData_0(r_RData_0), 
    
    .o_WEnable_1(), 
    .o_WAddr_1(),
    .o_WData_1(),
    .o_REnable_1(), 
    .o_RAddr_1(),
    .i_RData_1(32'd0), 
    
    .o_WEnable_2(out_WEnable_2), 
    .o_WAddr_2(out_WAddr_2),
    .o_WData_2(out_WData_2),
    .o_REnable_2(out_REnable_2), 
    .o_RAddr_2(out_RAddr_2),
    .i_RData_2(r_RData_2),
    
    .o_WEnable_3(), 
    .o_WAddr_3(),
    .o_WData_3(),
    .o_REnable_3(), 
    .o_RAddr_3(),
    .i_RData_3(32'd0), 
    
    .o_WEnable_4(), 
    .o_WAddr_4(),
    .o_WData_4(),
    .o_REnable_4(), 
    .o_RAddr_4(),
    .i_RData_4(32'd0), 
    
    .o_WEnable_5(), 
    .o_WAddr_5(),
    .o_WData_5(),
    .o_REnable_5(), 
    .o_RAddr_5(),
    .i_RData_5(32'd0),    
    
    .o_WEnable_6(), 
    .o_WAddr_6(),
    .o_WData_6(),
    .o_REnable_6(), 
    .o_RAddr_6(),
    .i_RData_6(32'd0) 
);


initial begin
    r_WEnable <= 0;
    r_REnable <= 0;
    r_WAddr <= 0;
    r_WData <= 0;
    r_RAddr <= 0;
    r_RData_0 <= 0;
    r_RData_2 <= 0;
    
    #10
    r_WAddr <= 12;
    r_WData <= 255;
    
    #5
    r_WEnable <= 1;
    
    #1
    r_WEnable <= 0;
    
    #30
    r_RAddr <= 1029;
    r_REnable <= 1;
    r_RData_2 <= 127;
    
    #1
    r_REnable <= 0;
    
    #30
    r_WAddr <= 1030;
    r_WData <= 1000;
    r_WEnable <= 1;
    
    #1
    r_WEnable <= 0;
    
    #50;

end

endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2024 12:17:07 AM
// Design Name: 
// Module Name: top_level
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


module top_level(
    // Sinais de clock e reset
    input i_Clk,
    input i_Rst,
    
    input [3:0] i_IntSources,
    
    output o_RData, 
    
    output led
);

// Conexões diretas entre os módulos
wire Wenable, Renable;
wire [31:0] wdata, rdata, waddr, raddr;
wire data_mem_busy;
wire o_Err_cpu;

//cpu to bus
 wire cpu_Clk;
 wire cpu_Rst;
 wire [`BUS_MSB:0] o_WAddr;
 wire [`BUS_MSB:0] o_WData;
 wire o_REnable;
 wire  [`BUS_MSB:0] o_RAddr;
 wire [`BUS_MSB:0] i_RData;        //vai diretamente ao write back, skip MEM/EXE reg
 
 wire intAckComplete, intAckAttended, intReq, intPending;
 wire [1:0] intNumber;

wire clk;

/*
  clk_wiz_0 inst
  (
  // Clock out ports  
  .clk_out1(clk),
  // Status and control signals               
  .reset(i_Rst), 
 // Clock in ports
  .clk_in1(i_Clk)
  );
  */


// Instanciando o memory_wrapper
memory_wrapper memory_instance(
    .i_Clk(i_Clk),
    .i_Rst(i_Rst),
    .i_WEnable(Wenable),
    .i_WAddr(waddr),
    .i_WData(wdata),
    .i_REnable(Renable),
    .i_RAddr(raddr),
    .o_RData(rdata),
    .o_Err(o_Err_CPU),
    .o_MemBusy(data_mem_busy)
);

// Instanciando o CPU
CPU cpu_instance(
    .i_Clk(i_Clk),
    .i_Rst(i_Rst),
    .o_Clk(cpu_Clk),
    .o_Rst(cpu_Rst),
    .o_WEnable(Wenable),
    .o_WAddr(waddr),
    .o_WData(wdata),
    .o_REnable(Renable),
    .o_RAddr(raddr),
    .i_RData(rdata),
    .i_DataMemRdy(data_mem_busy),
    
    .i_IntRequest(intReq),
    .i_IntNumber(intNumber),
    .i_IntPending(intPending),
    .o_IntAckComplete(intAckComplete),
    .o_IntAckAttended(intAckAttended),
    
    .led_teste(led)
);


interruptController interrupt_instance(
    .rst(i_Rst),
    .clk(i_Clk),
    .int_sources(i_IntSources),
    .int_pending(intPending),
    .int_ack_complete(intAckComplete),
    .int_ack_attended(intAckAttended),
    .int_req(intReq),
    .int_number(intNumber),
    .ea(1'b1),
    .en1(1'b1),
    .en2(1'b1),
    .en3(1'b1)
);

endmodule


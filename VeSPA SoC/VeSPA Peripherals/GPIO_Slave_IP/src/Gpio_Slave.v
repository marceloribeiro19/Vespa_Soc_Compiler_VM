module GPIO_Slave(
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
    input [3:0] pin_in,
    output [3:0] pin_out
);

reg [7:0] Wr_Output;
reg [7:0] direction; 
wire [7:0] Rd_Input;

integer i;

GPIO_PORT gpio(.direction(direction), .write_reg(Wr_Output), .read_reg(Rd_Input), .pin_in(pin_in), .pin_out(pin_out));

always @(posedge i_Clk) begin
    if (i_Rst) begin
        direction <= 0;
        Wr_Output <= 0;
        o_Err <= 0;
    end
    else begin
        
        if (i_WEnable) begin
            //Verify if the write address is within range
            case (i_WAddr)
                2'b00: begin
                    direction <= i_WData[7:0];
                    o_Err <= 0;
                end
            
                2'b01: begin
                   Wr_Output <= i_WData[7:0];
                   o_Err <= 0;
                end
                default: o_Err <= 1;
            endcase
        end
        //Check if there is a read request pending
        else if (i_REnable) begin
        
             case (i_RAddr)
                2'b00: begin
                    o_RData <= {24'b0, direction};                 
                    o_Err <= 0;
                end

                2'b01: begin
                    o_RData <= {24'b0, Wr_Output};
                    o_Err <= 0;
                end
                
                2'b10: begin
                    o_RData <= {24'b0, Rd_Input};
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


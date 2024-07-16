`timescale 1ns / 1ps

`define TIM_COUNTER_DEPTH       'd32
`define TIM_EVENT_COUNTER_DEPTH 'd32
`define TIM_DIVISOR_DEPTH       'd2
`define TIM_MODE_DEPTH          'd2
`define TIM_PWM_COUNTER_DEPTH   'd8
`define TIM_PWM_CH_EN_DEPTH     'd4
`define TIM_PULSE_LEN_DEPTH     'd16


`define COUNTER_RESET_VALUE     'd0
`define COUNTER_OVERFLOW_VALUE  32'hFFFFFFFF

// Timer Modes
`define TIM_TIMER_MODE          2'b00
`define TIM_COUNTER_MODE        2'b01
`define TIM_PWM_MODE            2'b10
`define TIM_ONE_PULSE_MODE      2'b11

// Timer Divisor
`define TIM_DIVISOR_1           2'b00
`define TIM_DIVISOR_2           2'b01
`define TIM_DIVISOR_4           2'b10
`define TIM_DIVISOR_8           2'b11

// PWM
`define PWM_CHANNEL_1_INDEX     'd0
`define PWM_CHANNEL_2_INDEX     'd1
`define PWM_CHANNEL_3_INDEX     'd2
`define PWM_CHANNEL_4_INDEX     'd3

module Timer
(
    input wire i_clk,                                           // Clock input
    input wire i_rst,                                           // Reset input
    
    input wire [`TIM_COUNTER_DEPTH-1:0] i_Period,               // Input for the user to set the desired time or PWM duty cycle
    input wire [`TIM_DIVISOR_DEPTH-1:0] i_Divisor,              // CLock divisor
    input wire [`TIM_MODE_DEPTH-1:0]    i_Mode,                 // Mode selection input (0: timer, 1: event counter, 2: PWM, 3: one pulse)
    
    input wire [`TIM_PULSE_LEN_DEPTH-1:0]   i_OnePulseLength,   // One pulse length
    
    input wire [`TIM_PWM_CH_EN_DEPTH-1:0]   i_ChannelEnable,    // Register to enable channel PWM output
    input wire [`TIM_PWM_COUNTER_DEPTH-1:0] i_PulseChannel1,    // PWM channel 1 pulse value
    input wire [`TIM_PWM_COUNTER_DEPTH-1:0] i_PulseChannel2,    // PWM channel 2 pulse value
    input wire [`TIM_PWM_COUNTER_DEPTH-1:0] i_PulseChannel3,    // PWM channel 3 pulse value
    input wire [`TIM_PWM_COUNTER_DEPTH-1:0] i_PulseChannel4,    // PWM channel 4 pulse value
    
    input wire i_Enable,                                        // Enable
    input wire i_AutoReload,                                    // Auto-reload
    
    output wire [`TIM_EVENT_COUNTER_DEPTH-1:0] o_EventCounter,  // Event counter output
    output wire o_TimerOverflow,                                // Timer overflow output
    output reg  o_PWMChannel1,                                  // PWM Channel 1 output
    output reg  o_PWMChannel2,                                  // PWM Channel 2 output
    output reg  o_PWMChannel3,                                  // PWM Channel 3 output
    output reg  o_PWMChannel4,                                  // PWM Channel 4 output
    output reg  o_OnePulseOut                                   // One Pulse output
);

// Counters
reg [`TIM_COUNTER_DEPTH-1:0]     r_Counter;      // Timer counter 
reg [`TIM_COUNTER_DEPTH-1:0]     r_EventCounter; // Event counter
reg [`TIM_PWM_COUNTER_DEPTH-1:0] r_PWMCounter;   // PWM dedicated counter

// Flags
reg r_TimerOverflow;                             // Overflow flag
reg r_PulseGeneration;                           // Pulse generation started flag

// Divisor CLocks
reg r_DivisorClk2;
reg r_DivisorClk4;
reg r_DivisorClk8;

wire w_TimerClk;

always @(posedge i_clk)         r_DivisorClk2  <= ~r_DivisorClk2;
always @(posedge r_DivisorClk2) r_DivisorClk4  <= ~r_DivisorClk4;
always @(posedge r_DivisorClk4) r_DivisorClk8  <= ~r_DivisorClk8;

assign w_TimerClk = (i_Divisor == `TIM_DIVISOR_2) ? r_DivisorClk2 :
                    (i_Divisor == `TIM_DIVISOR_4) ? r_DivisorClk4 :
                    (i_Divisor == `TIM_DIVISOR_8) ? r_DivisorClk8 :
                    i_clk;

always @(posedge w_TimerClk)
begin
    if (i_rst) begin
        r_Counter <= `COUNTER_RESET_VALUE;      // Reset timer counter
        r_PWMCounter <= `COUNTER_RESET_VALUE;   // Reset PWM counter
        r_EventCounter <= `COUNTER_RESET_VALUE; // Reset Event Count
        r_PulseGeneration <= 1'b0;
        
        r_DivisorClk2 <= 'b0;                   // Reset Divisor /2 register
        r_DivisorClk4 <= 'b0;                   // Reset Divisor /4 register
        r_DivisorClk8 <= 'b0;                   // Reset Divisor /8 register
        
        r_TimerOverflow <= 1'b0;                // Reset the overflow flag
        o_OnePulseOut   <= 1'b0;                // Reset One Pulse output
        
        o_PWMChannel1 <= 1'b0;                  // Reset PWM channel 1 output
        o_PWMChannel2 <= 1'b0;                  // Reset PWM channel 2 output
        o_PWMChannel3 <= 1'b0;                  // Reset PWM channel 3 output
        o_PWMChannel4 <= 1'b0;                  // Reset PWM channel 4 output
    end
    else if (i_Enable) begin
        case (i_Mode)
            // ------------- Timer Mode -------------
            `TIM_TIMER_MODE:
            begin                
                if (r_Counter == i_Period)
                begin
                    r_TimerOverflow <= 1'b1;                // Signalize timer overflow
                    
                    if(i_AutoReload)                        // If auto-reload enabled reset counter
                        r_Counter <= `COUNTER_RESET_VALUE;
                end 
                else
                begin
                    r_Counter <= r_Counter + 1;             // Increment counter
                    r_TimerOverflow <= 0;
                end
            end
            
            // ------------- Counter Mode -------------
            `TIM_COUNTER_MODE:
            begin
                r_EventCounter <= r_EventCounter + 1;     // Increment Event Counter while i_enabled is set
            end
            
            // ------------- PWM Mode -------------
            `TIM_PWM_MODE:
            begin
                if (r_PWMCounter == i_Period)
                    r_PWMCounter = `COUNTER_RESET_VALUE;   // Reset PWM counter
                
                r_PWMCounter  = r_PWMCounter + 1;          // Increment the Counter on each clock edge
                
                o_PWMChannel1 = ((r_PWMCounter < i_PulseChannel1 || r_PWMCounter == i_PulseChannel1) && i_ChannelEnable[`PWM_CHANNEL_1_INDEX]) ? 1'b1 : 1'b0;
                o_PWMChannel2 = ((r_PWMCounter < i_PulseChannel2 || r_PWMCounter == i_PulseChannel2) && i_ChannelEnable[`PWM_CHANNEL_2_INDEX]) ? 1'b1 : 1'b0;
                o_PWMChannel3 = ((r_PWMCounter < i_PulseChannel3 || r_PWMCounter == i_PulseChannel3) && i_ChannelEnable[`PWM_CHANNEL_3_INDEX]) ? 1'b1 : 1'b0;
                o_PWMChannel4 = ((r_PWMCounter < i_PulseChannel4 || r_PWMCounter == i_PulseChannel4) && i_ChannelEnable[`PWM_CHANNEL_4_INDEX]) ? 1'b1 : 1'b0;
            end
            
            // ------------- One Pulse Mode -------------
            `TIM_ONE_PULSE_MODE:
            begin
                if(!r_PulseGeneration)
                // Time until pulse is generated
                begin
                    if (r_Counter == i_Period)
                    begin
                        r_PulseGeneration <= 1'b1;
                        r_Counter <= `COUNTER_RESET_VALUE;
                        
                        o_OnePulseOut <= 1'b1;
                    end 
                    else
                        r_Counter <= r_Counter + 1;
                end
                else
                // Pulse generation
                begin
                    if (r_Counter == i_OnePulseLength)
                        o_OnePulseOut <= 1'b0;
                    else
                        r_Counter <= r_Counter + 1;
                end
            end
            
            default:
            begin
                r_Counter       <= `COUNTER_RESET_VALUE;  // Reset Counter
                r_EventCounter  <= `COUNTER_RESET_VALUE;  // Reset Event counter
                r_PWMCounter    <= `COUNTER_RESET_VALUE;  // Reset PWM counter
                
                r_TimerOverflow <= 1'b0;      // Reset Timer Overflow flag
                
                o_OnePulseOut   <= 1'b0;     // Reset One Pulse output
                
                o_PWMChannel1   <= 1'b0;     // Reset PWM channel 1 output
                o_PWMChannel2   <= 1'b0;     // Reset PWM channel 2 output
                o_PWMChannel3   <= 1'b0;     // Reset PWM channel 3 output
                o_PWMChannel4   <= 1'b0;     // Reset PWM channel 4 output
                
            end
        endcase
    end
    else
    begin
        case (i_Mode)
            // ------------- Timer Mode -------------
            `TIM_TIMER_MODE:
            begin                
                r_Counter <= `COUNTER_RESET_VALUE;
                r_TimerOverflow <= 0;
            end
            
            // ------------- Counter Mode -------------
            `TIM_COUNTER_MODE:
            begin
                r_EventCounter <= `COUNTER_RESET_VALUE; // Reset the Event counter
            end
            
            // ------------- PWM Mode -------------
            `TIM_PWM_MODE:
            begin
                r_PWMCounter  <= `COUNTER_RESET_VALUE;  // Reset PWM counter
                
                o_PWMChannel1 <= 1'b0;                  // Reset PWM channel 1 output
                o_PWMChannel2 <= 1'b0;                  // Reset PWM channel 2 output
                o_PWMChannel3 <= 1'b0;                  // Reset PWM channel 3 output
                o_PWMChannel4 <= 1'b0;                  // Reset PWM channel 4 output
            end
            
            // ------------- One Pulse Mode -------------
            `TIM_ONE_PULSE_MODE:
            begin
                r_Counter <= `COUNTER_RESET_VALUE;      // Reset Counter
                
                o_OnePulseOut <= 1'b0;                  // Reset One Pulse output
            end
            
            default:
            // Reset everything in case of invalid Timer mode
            begin
                r_Counter       <= `COUNTER_RESET_VALUE;  // Reset Counter
                r_EventCounter  <= `COUNTER_RESET_VALUE;  // Reset Event counter
                r_PWMCounter    <= `COUNTER_RESET_VALUE;  // Reset PWM counter
                
                r_TimerOverflow <= 1'b0;      // Reset Timer Overflow flag
                
                o_OnePulseOut   <= 1'b0;     // Reset One Pulse output
                
                o_PWMChannel1   <= 1'b0;     // Reset PWM channel 1 output
                o_PWMChannel2   <= 1'b0;     // Reset PWM channel 2 output
                o_PWMChannel3   <= 1'b0;     // Reset PWM channel 3 output
                o_PWMChannel4   <= 1'b0;     // Reset PWM channel 4 output
                
            end
        endcase  
    end
end

assign o_TimerOverflow = r_TimerOverflow;

assign o_EventCounter  = r_EventCounter;

endmodule
`timescale 1ns / 1ps
//Author: Jianjian Song
//Date:	January 2017
//ECE530 Winter 2016-2017
//A complete UART module based on files from Xilinx
module UARTmodule2016winter(rx, tx, tx_full, rx_data_present, read_from_uart, write_to_uart, 
rx_data, tx_data, transmitted_bits, clock, reset);
output	tx;
input 	rx;
output  	tx_full, rx_data_present;;
input read_from_uart, write_to_uart;
input  clock, reset;
output reg [TRANSMITTED_BITS-1:0] transmitted_bits;
input [7:0] tx_data;
output [7:0] 	rx_data;
parameter TRANSMITTED_BITS=8'd4, BAUDRATE=20'd19200, FREQUENCY=30'd100000000;
wire  en_16_x_baud;

always@(posedge clock)
 transmitted_bits<=tx_data;

	BaudRateGenerator BaudRateUnit(en_16_x_baud, reset, clock, BAUDRATE, FREQUENCY);

wire read_one_shot, write_one_shot;
//module ClockedOneShot(InputPulse, OneShot, Reset, CLOCK) ;
ClockedOneShot ReadOneShotUnit(read_from_uart, read_one_shot, reset, clock) ;

ClockedOneShot WriteOneShotUnit(write_to_uart, write_one_shot, reset, clock) ;

// Signals for UART connections
//reg read_from_uart, write_to_uart;

wire  	tx_half_full;
wire  	rx_full;
wire  	rx_half_full;

uart_tx TransmitUnit(	.data_in(tx_data), .write_buffer(write_one_shot),
    	.reset_buffer(1'b0), .en_16_x_baud(en_16_x_baud),
    	.serial_out(tx),.buffer_full(tx_full),
    	.buffer_half_full(),.clk(clock));
		
uart_rx ReceiveUnit
(	.serial_in(rx),
    	.data_out(rx_data),
    	.read_buffer(read_one_shot),
    	.reset_buffer(1'b0),
    	.en_16_x_baud(en_16_x_baud),
    	.buffer_data_present(rx_data_present),
    	.buffer_full(rx_full),
    	.buffer_half_full(rx_half_full),
    	.clk(clock));
endmodule

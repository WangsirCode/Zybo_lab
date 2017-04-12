// (c) Copyright 1995-2017 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:user:UARTmodule2016winter:1.0
// IP Revision: 2

`timescale 1ns/1ps

(* DowngradeIPIdentifiedWarnings = "yes" *)
module system_UARTmodule2016winter_0_0 (
  rx,
  tx,
  tx_full,
  rx_data_present,
  read_from_uart,
  write_to_uart,
  rx_data,
  tx_data,
  transmitted_bits,
  clock,
  reset
);

input wire rx;
output wire tx;
output wire tx_full;
output wire rx_data_present;
input wire read_from_uart;
input wire write_to_uart;
output wire [7 : 0] rx_data;
input wire [7 : 0] tx_data;
output wire [3 : 0] transmitted_bits;
input wire clock;
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 signal_reset RST" *)
input wire reset;

  UARTmodule2016winter #(
    .TRANSMITTED_BITS('B00000100),
    .BAUDRATE('H04B00),
    .FREQUENCY('B000101111101011110000100000000)
  ) inst (
    .rx(rx),
    .tx(tx),
    .tx_full(tx_full),
    .rx_data_present(rx_data_present),
    .read_from_uart(read_from_uart),
    .write_to_uart(write_to_uart),
    .rx_data(rx_data),
    .tx_data(tx_data),
    .transmitted_bits(transmitted_bits),
    .clock(clock),
    .reset(reset)
  );
endmodule

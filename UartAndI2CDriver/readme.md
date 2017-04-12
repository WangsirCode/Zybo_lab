# Custom IP of a UART in Verilog and Standard Terminal to Display Two TMP101s from MIO and SelectIO

## Procedure

- Create an IP for a UART in Verilog from uart source files in Verilog provided by the instructor.
- Create a new Vivado RTL project . Add your UART IP to this block design.
- Write your program for this new hardware block design to display two temperatures from two TMP101 modules on both standard and your custom IP UART terminal that is connected to your FTDI breakout board.
- The TMP101 breakout board in Port F is connected to the PS through MIO pins and is connected to Port F are as follows: SDK on JF9 (M14) and SDA on JF10 (M15). The TMP101 on Port B is connected to the PS through SelectIO pins and is connected so that JB3 (V20) is SCL and JB4 (W20) is SDA. The custom UART is connected to Pmod C. transmitted_bits are displayed on the four LEDs.


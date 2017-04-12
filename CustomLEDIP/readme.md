# Custom led ip 
## introducion

This lab guides you through the process of writing a basic software application. The software you will develop will write to the LEDs on the Zynq board. An AXI BRAM controller and associated 8KB BRAM were added in the last lab. The application will be run from the BRAM by modifying the linker script for the project to place the text section of the application in the BRAM. You will verify that the design operates as expected, by testing in hardware.

## Procedure

You will open the Vivado project, export to and invoke SDK, create a software project, analyze assembled object files and verify the design in hardware.
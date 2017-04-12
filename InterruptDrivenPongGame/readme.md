# Interrupt-Driven Ping-Pong Game on Zybo

## The Architecture of the Interrupt Driven LED Ping-Pong Game

This game is composed of three major subroutines: main(), push button interrupt handler and
timer interrupt handler. The main program will set up interrupts and initialize all ports and
timer. The main program will then print on the terminal of the game status and results. The two
interrupt handlers will deal with push buttons and timer interrupts.
Push button interrupt handler will decide which button is pressed and set game status and result
accordingly.
Timer interrupt handler will update LED display.
Global status and result variables are used to communicate among the three major subroutines.
/*
 * Pingpong_template.h
 *
 *  Created on: 3/27/2017
 *  Author: wangyuhao
 */

#ifndef PINGPONG_TEMPLATE_H_
#define PINGPONG_TEMPLATE_H_

#define TRM_OVERFLOW ~(u32)0
#define TRM_LOAD     0x07FFFFFF
#define BTN_INT XGPIO_IR_CH1_MASK

//game status
#define START 1
#define STOP 0

//directions
#define LEFT 0
#define RIGHT 1

//button status
#define RESETBUTTON 0b0100
#define STARTBUTTON 0b0010
#define LEFTPADDLE 0b1000
#define RIGHTPADDLE 0b0001

//LED status
#define RIGHT_INIT_STATE 0
#define LEFT_INIT_STATE 3
#define LEFT_END 0
#define RIGHT_END 3

#define local static
int psb_check, dip_check, LedState, Status,count,dip_check_prev;

//I/O s
XGpio dip, push;

XTmrCtr TMRInst;

XScuGic INTCInst;

int LED_PATTERNS[4]={0b0001, 0b0010, 0b0100,0b1000};
int scoreright, scoreleft;
char GameOver, StartDirection,LEDDirection;


local int initialize();
local void setStatus();
local void setTimer();
local void setLED();
local void BTN_Intr_Handler(void *baseaddr_p);
local void TMR_Intr_Handler(void *baseaddr_p);
local int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
local int IntcInitFunction(u16 DeviceId, XTmrCtr *TmrInstancePtr, XGpio *GpioInstancePtr);


#endif /* PINGPONG_TEMPLATE_H_ */
